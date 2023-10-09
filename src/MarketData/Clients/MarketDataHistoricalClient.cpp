//
// Created by Michael Lewis on 9/28/23.
//

#include <functional>
#include <memory>
#include <utility>
#include <vector>
#include <string>

#include <databento/historical.hpp>

#include "MarketDataHistoricalClient.hpp"
#include "MarketData/MarketDataUtils.hpp"
#include "MarketDataStreamingClient.hpp"
#include "MarketData/Processors/MarketDataProcessor.hpp"
#include "CommonServer/Utils/ConfigManager.hpp"
#include "CommonServer/Utils/LogLevel.hpp"

namespace BeaconTech::MarketData
{
    // Overloaded ctor that initializes the client and downstream components
    MarketDataHistoricalClient::MarketDataHistoricalClient(std::string clientName)
        : IMarketDataProvider{}, clientName{std::move(clientName)},
          client{std::make_shared<databento::Historical>(MarketDataUtils::getHistoricalClient())},
          streamingClient{std::make_shared<MarketDataStreamingClient<MarketDataHistoricalClient>>(*this)}
    {
        streamingClient->initialize();
    }

    // Dtor that currently terminates session gateway with MarketDataClient
    MarketDataHistoricalClient::~MarketDataHistoricalClient()
    {
        stop();
    }

    // The system will ultimately have numerous market data clients (e.g. strategies for live trading,
    // a market data writer to persist ticks for backtesting, etc.) The clientName will be useful in
    // identifying which market data clients have connected or are working via logging.
    const std::string& MarketDataHistoricalClient::getClientName() const
    {
        return clientName;
    }

    std::shared_ptr<IMarketDataProvider> MarketDataHistoricalClient::getClient() const
    {
        return std::make_shared<MarketDataHistoricalClient>(*this);
    }

    // Batch download historical data files for back-testing. Note - This can be converted into a
    // streaming download using the streaming API; however, streaming incurs a per stream costs
    // whereas batch download only incurs a cost for the first download. All subsequent downloads are free
    std::vector<std::string> MarketDataHistoricalClient::doBatchDownload(const std::shared_ptr<databento::Historical>& _client)
    {
        // Batch download historical data files for back-testing
        return _client->BatchDownload(
                Utils::ConfigManager::stringConfig("marketData"),
                Utils::ConfigManager::stringConfig("fileToDownload"));
    }

    // Read from a file previously downloaded to avoid for testing. Will eventually need to migrate over to
    // the batch download or persist tick data to AWS so that we can replay previously trading days
    // when back-testing instead of running batch downloads for each back-test.
    std::vector<std::string> MarketDataHistoricalClient::readFromFile()
    {
        return {Utils::ConfigManager::stringConfig("flatHistoricalDataFile")};
    }

    // Used by the MarketDataConsumer to consume bookUpdates published by the market data provider (pub-sub model)
    std::function<void ()> MarketDataHistoricalClient::getBookUpdate(MarketDataProcessor& streamingProcessor)
    {
        return [&]() {
            try
            {
                // todo - Reading from previously downloaded file for testing purposes.
                // std::vector<std::string> bookUpdates = doBatchDownload(client);
                std::vector<std::string> bookUpdates = readFromFile();

                // Replay each book update by providing a callback processor to the clients Replay API
                for (const auto& bookUpdate : bookUpdates)
                {
                    if (bookUpdate.substr(bookUpdate.length() - 8) == ".dbn.zst")
                    {
                        auto callback = [&] (const databento::Record& record)
                        {
                            return streamingProcessor.processBookUpdate(record);
                        };

                        databento::DbnFileStore dbn_store{bookUpdate};
                        dbn_store.Replay(callback);
                    }
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

    void MarketDataHistoricalClient::stop()
    {
        MarketDataUtils::log(Utils::LogLevel::INFO, "Terminated session gateway with MarketDataClient");
    }
} // namespace BeaconTech::MarketData