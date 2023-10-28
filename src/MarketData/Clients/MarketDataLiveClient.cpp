//
// Connects to a market data provider using a subscription style protocol. This client
// communicates with the providers real-time data gateway using the C++ API.
//
// Created by Michael Lewis on 9/29/23.
//


#include <functional>
#include <memory>
#include <string>

#include <databento/live.hpp>
#include <databento/log.hpp>

#include "MarketDataLiveClient.hpp"
#include "MarketDataStreamingClient.hpp"
#include "MarketData/MarketDataUtils.hpp"
#include "CommonServer/logging/LogLevel.hpp"
#include "CommonServer/typesystem/MdTypes.hpp"

using namespace std::chrono_literals;

namespace BeaconTech::MarketData
{
    // Overloaded ctor that initializes the client and downstream components
    MarketDataLiveClient::MarketDataLiveClient(std::string clientName)
        : IMarketDataProvider{}, clientName{std::move(clientName)},
          client{std::make_shared<databento::LiveBlocking>(MarketDataUtils::getLiveClient())},
          streamingClient{std::make_shared<MarketDataStreamingClient<MarketDataLiveClient>>()}
    {

    }

    // The system will ultimately have numerous market data clients (e.g. strategies for live trading,
    // a market data writer to persist ticks for backtesting, etc.) The clientName will be useful in
    // identifying which market data clients have connected or are working via logging.
    const std::string& MarketDataLiveClient::getClientName() const
    {
        return clientName;
    }

    // Allows system components to subscribe to book updates via a callback
    void MarketDataLiveClient::subscribe(std::shared_ptr<MarketDataLiveClient> marketDataClient, const Common::MdCallback& callback)
    {
        streamingClient->initialize(marketDataClient, callback);
    }

    // Used by the MarketDataConsumer to consume bookUpdates published by the market data provider (pub-sub model)
    std::function<void ()> MarketDataLiveClient::getBookUpdate(std::shared_ptr<MarketDataProcessor>& streamingProcessor)
    {
        return [&]() {
            try
            {
                // Add a new subscription to the session with the Databento live gateway
                client->Subscribe({}, databento::Schema::Mbo, databento::SType::RawSymbol);

                // Instructs the live gateway to start sending data
                client->Start();

                // Blocks until the next record is received or the optional timeout is reached
                // A full list of fields returned through the record_callback or nullptr if no record was received
                auto* bookUpdate = client->NextRecord(1ms);

                // Use template keyword to treat Holds as a dependent type to Record
                if (bookUpdate && bookUpdate->template Holds<databento::MboMsg>())
                {
                    streamingProcessor->processBookUpdate(*bookUpdate);
                }
                else
                {
                    MarketDataUtils::log(Common::LogLevel::WARN, "Timed out waiting for record");
                }
            }
            catch (const databento::HttpResponseError& e)
            {
                MarketDataUtils::log(Common::LogLevel::SEVERE, e.what());
            }
            catch (const std::exception& e)
            {
                MarketDataUtils::log(Common::LogLevel::SEVERE, e.what());
            }
        };
    }

    // Closes the session gateway. Once closed, the session cannot be restarted.
    void MarketDataLiveClient::stop()
    {
        client->Stop();
        MarketDataUtils::log(Common::LogLevel::INFO, "Terminated session gateway with MarketDataClient");
    }
} // namespace BeaconTech::marketdata