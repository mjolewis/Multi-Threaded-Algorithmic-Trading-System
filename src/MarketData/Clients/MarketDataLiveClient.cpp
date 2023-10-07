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
#include "CommonServer/Utils/LogLevel.hpp"

using namespace std::chrono_literals;

namespace BeaconTech::MarketData
{
    // Overloaded ctor that initializes the client and downstream components
    MarketDataLiveClient::MarketDataLiveClient(std::string clientName)
        : IMarketDataProvider{}, clientName{std::move(clientName)},
          client{std::make_shared<databento::LiveBlocking>(MarketDataUtils::getLiveClient())},
          streamingClient{std::make_shared<MarketDataStreamingClient<MarketDataLiveClient>>(*this)}
    {
        streamingClient->initialize();
    }

    // Dtor that currently terminates session gateway with MarketDataClient
    MarketDataLiveClient::~MarketDataLiveClient()
    {
        stop();
    }

    // The system will ultimately have numerous market data clients (e.g. strategies for live trading,
    // a market data writer to persist ticks for backtesting, etc.) The clientName will be useful in
    // identifying which market data clients have connected or are working via logging.
    const std::string& MarketDataLiveClient::getClientName() const
    {
        return clientName;
    }

    std::shared_ptr<IMarketDataProvider> MarketDataLiveClient::getClient() const
    {
        return std::make_shared<MarketDataLiveClient>(*this);
    }

    // Used by the MarketDataConsumer to consume bookUpdates published by the market data provider (pub-sub model)
    std::function<void ()> MarketDataLiveClient::getBookUpdate(MarketDataProcessor& streamingProcessor)
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
                    streamingProcessor.processBookUpdate(*bookUpdate);
                }
                else
                {
                    MarketDataUtils::log(Utils::LogLevel::WARN, "Timed out waiting for record");
                }
            }
            catch (const databento::HttpResponseError& e)
            {
                MarketDataUtils::log(Utils::LogLevel::SEVERE, e.what());
            }
            catch (const std::exception& e)
            {
                MarketDataUtils::log(Utils::LogLevel::SEVERE, e.what());
            }
        };
    }

    // Stops the session with the gateway. Once stopped, the session cannot be restarted.
    void MarketDataLiveClient::stop()
    {
        client->Stop();
        MarketDataUtils::log(Utils::LogLevel::INFO, "Terminated session gateway with MarketDataClient");
    }
} // namespace BeaconTech::MarketData