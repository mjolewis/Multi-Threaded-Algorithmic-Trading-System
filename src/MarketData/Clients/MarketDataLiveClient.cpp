//
// Created by Michael Lewis on 9/29/23.
//

#include <functional>
#include <memory>

#include <databento/live.hpp>
#include <databento/log.hpp>

#include "MarketDataLiveClient.hpp"
#include "MarketDataStreamingClient.hpp"
#include "src/MarketData/MarketDataUtils.hpp"

using namespace std::chrono_literals;

namespace MarketData
{
    // Overloaded ctor that initializes the client and downstream components
    MarketDataLiveClient::MarketDataLiveClient() : IMarketDataProvider{},
        client{std::make_shared<databento::LiveBlocking>(MarketDataUtils::getLiveClient())},
        streamingClient{std::make_shared<MarketDataStreamingClient<MarketDataLiveClient>>(*this)}
    {
        streamingClient->initialize();
    }

    std::shared_ptr<IMarketDataProvider> MarketDataLiveClient::getClient() const
    {
        return std::make_shared<MarketDataLiveClient>(*this);
    }

    // Used by the MarketDataConsumer to consume bookUpdates published by the market data provider (pub-sub model)
    std::function<void ()> MarketDataLiveClient::getBookUpdate() const
    {
        return [&_client = client]() {
            try
            {
                // Add a new subscription to the session with the Databento live gateway
                _client->Subscribe({}, databento::Schema::Mbo, databento::SType::RawSymbol);

                // Instructs the live gateway to start sending data
                _client->Start();

                // Blocks until the next record is received or the optional timeout is reached
                // A full list of fields returned through the record_callback or nullptr if no record was received
                auto* bookUpdate = _client->NextRecord(1ms);

                // Use template keyword to treat Holds as a dependent type to Record
                if (bookUpdate && bookUpdate->template Holds<databento::MboMsg>())
                {
                    MarketDataProcessor::processBookUpdate(*bookUpdate);
                }
                else
                {
                    MarketDataUtils::logErrorMessage(1, "Timed out waiting for record");
                }
            }
            catch (const databento::HttpResponseError& e)
            {
                MarketDataUtils::logErrorMessage(1, e.what());
            }
            catch (const std::exception& e)
            {
                MarketDataUtils::logErrorMessage(1, e.what());
            }
        };
    }

    // Stops the session with the gateway. Once stopped, the session cannot be restarted.
    void MarketDataLiveClient::stop()
    {
        client->Stop();
    }
}