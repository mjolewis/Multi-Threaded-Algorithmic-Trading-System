//
// Connects to a market data provider using an HTTP style protocol. This client
// communicates with the providers historical data gateway using the C++ API.
// Historical data can be streamed or loaded data directly into the application.
// The provider also provides an API to make batch download requests, which instructs
// the service to prepare the data as flat files.
//
// Created by Michael Lewis on 9/29/23.
//

#include <memory>
#include <utility>
#include <vector>
#include <string>

#include <databento/historical.hpp>

#include "MarketDataHistoricalClient.hpp"
#include "MarketData/MarketDataUtils.hpp"
#include "MarketDataStreamingClient.hpp"
#include "MarketData/processors/MarketDataProcessor.hpp"
#include "CommonServer/utils/ConfigManager.hpp"
#include "CommonServer/logging/LogLevel.hpp"

namespace BeaconTech::MarketData
{
    // Overloaded ctor that initializes the client and downstream components
    MarketDataHistoricalClient::MarketDataHistoricalClient(std::string clientName)
        : IMarketDataProvider{}, clientName{std::move(clientName)},
          client{std::make_shared<databento::Historical>(MarketDataUtils::getHistoricalClient())},
          streamingClient{std::make_shared<MarketDataStreamingClient<MarketDataHistoricalClient>>()}
    {

    }

    // The system will ultimately have numerous market data clients (e.g. strategies for live trading,
    // a market data writer to persist ticks for backtesting, etc.) The clientName will be useful in
    // identifying which market data clients have connected or are working via logging.
    const std::string& MarketDataHistoricalClient::getClientName() const
    {
        return clientName;
    }

    // Allows system components to subscribe to book updates via a callback
    void MarketDataHistoricalClient::subscribe(std::shared_ptr<MarketDataHistoricalClient> marketDataClient,
                                               const Common::MdCallback& callback)
    {

        streamingClient->initialize(marketDataClient, callback);
    }

    // Batch download historical data files for back-testing. Note - This can be converted into a
    // streaming download using the streaming API; however, streaming incurs a per stream costs
    // whereas batch download only incurs a cost for the first download. All subsequent downloads are free
    std::vector<std::string> MarketDataHistoricalClient::doBatchDownload(const std::shared_ptr<databento::Historical>& _client)
    {
        // Batch download historical data files for back-testing
        return _client->BatchDownload(
                Common::ConfigManager::stringConfigValueDefaultIfNull("marketData", "../src/marketdata/historicaldata"),
                Common::ConfigManager::stringConfigValueDefaultIfNull("fileToDownload", ""));
    }

    // Read from a file previously downloaded to avoid for testing. Will eventually need to migrate over to
    // the batch download or persist tick data to AWS so that we can replay previously trading days
    // when back-testing instead of running batch downloads for each back-test.
    std::vector<std::string> MarketDataHistoricalClient::readFromFile()
    {
        return {Common::ConfigManager::stringConfigValueDefaultIfNull("flatHistoricalDataFile", "")};
    }

    // Used by the MarketDataConsumer to consume bookUpdates published by the market data provider (pub-sub model)
    std::function<void ()> MarketDataHistoricalClient::getBookUpdate(std::shared_ptr<MarketDataProcessor>& streamingProcessor)
    {
        return [&]() {
            try
            {
                // todo - Reading from previously downloaded file for demo purposes.
                // std::vector<std::string> bookUpdates = doBatchDownload(client);
                std::vector<std::string> bookUpdates = readFromFile();

                // Replay each book update by providing a callback processor to the clients Replay API
                for (const auto& bookUpdate : bookUpdates)
                {
                    if (bookUpdate.substr(bookUpdate.length() - 8) == ".dbn.zst")
                    {
                        auto callback = [&] (const databento::Record& record)
                        {
                            return streamingProcessor->processBookUpdate(record);
                        };

                        databento::DbnFileStore dbn_store{bookUpdate};
                        dbn_store.Replay(callback);
                    }
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
    void MarketDataHistoricalClient::stop()
    {
        MarketDataUtils::log(Common::LogLevel::INFO, "Terminated session gateway with MarketDataClient");
    }
} // namespace BeaconTech::marketdata