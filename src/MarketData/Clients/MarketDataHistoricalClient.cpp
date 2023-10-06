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
#include "src/MarketData/MarketDataUtils.hpp"
#include "MarketDataStreamingClient.hpp"
#include "src/Resources/ConfigReader.hpp"
#include "src/MessageObjects/LogLevels/LogLevel.hpp"

namespace MarketData
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
                Utilities::ConfigReader::extractStringValueFromConfig("marketData"),
                Utilities::ConfigReader::extractStringValueFromConfig("fileToDownload"));
    }

    // Read from a file previously downloaded to avoid for testing. Will eventually need to migrate over to
    // the batch download or persist tick data to AWS so that we can replay previously trading days
    // when back-testing instead of running batch downloads for each back-test.
    std::vector<std::string> MarketDataHistoricalClient::readFromFile()
    {
        return {"/Users/mlewis/CLionProjects/Multi-Threaded-Algorithmic-Trading-System/src/MarketData/HistoricalData/XNAS-20230927-798SMC6CUJ/xnas-itch-20230925.mbo.dbn.zst"};
    }

    // Used by the MarketDataConsumer to consume bookUpdates published by the market data provider (pub-sub model)
    std::function<void ()> MarketDataHistoricalClient::getBookUpdate() const
    {
        return [&_client = client]() {
            try
            {
                // todo - Reading from previously downloaded file for testing purposes.
                std::vector<std::string> bookUpdates = doBatchDownload(_client);
                // std::vector<std::string> bookUpdates = readFromFile();

                // Replay each book update by providing a callback processor to the clients Replay API
                for (const auto& bookUpdate : bookUpdates)
                {
                    if (bookUpdate.substr(bookUpdate.length() - 8) == ".dbn.zst")
                    {
                        databento::DbnFileStore dbn_store{bookUpdate};
                        dbn_store.Replay(MarketDataProcessor::processBookUpdate);
                    }
                }
            }
            catch (const databento::HttpResponseError& e)
            {
                MarketDataUtils::log(MessageObjects::LogLevel::SEVERE, e.what());
            }
            catch (const std::exception& e)
            {
                MarketDataUtils::log(MessageObjects::LogLevel::SEVERE, e.what());
            }
        };
    }

    void MarketDataHistoricalClient::stop()
    {
        MarketDataUtils::log(MessageObjects::LogLevel::INFO, "Terminated session gateway with MarketDataClient");
    }
}