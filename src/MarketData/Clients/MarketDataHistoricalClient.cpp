//
// Created by Michael Lewis on 9/28/23.
//

#include <functional>
#include <memory>

#include <databento/historical.hpp>

#include "MarketDataHistoricalClient.hpp"
#include "src/MarketData/MarketDataUtils.hpp"
#include "MarketDataStreamingClient.hpp"
#include "src/Resources/ConfigReader.hpp"

namespace MarketData
{
    // Overloaded ctor that initializes the client and downstream components
    MarketDataHistoricalClient::MarketDataHistoricalClient() : IMarketDataProvider{},
        client{std::make_shared<databento::Historical>(MarketDataUtils::getHistoricalClient())},
        streamingClient{std::make_shared<MarketDataStreamingClient<MarketDataHistoricalClient>>(*this)}
    {
        streamingClient->initialize();
    }

    std::shared_ptr<IMarketDataProvider> MarketDataHistoricalClient::getClient() const
    {
        return std::make_shared<MarketDataHistoricalClient>(*this);
    }

    // Used by the MarketDataConsumer to consume bookUpdates published by the market data provider (pub-sub model)
    std::function<void ()> MarketDataHistoricalClient::getBookUpdate() const
    {
        return [&_client = client]() {

            // Batch download historical data files for back-testing
            auto bookUpdates = _client->BatchDownload(
                    Utilities::ConfigReader::extractStringValueFromConfig("marketData"),
                    Utilities::ConfigReader::extractStringValueFromConfig("fileToDownload"));

            // Replay each book update by providing a callback processor to the clients Replay API
            for (const auto& bookUpdate : bookUpdates)
            {
                if (bookUpdate.substr(bookUpdate.length() - 8) == ".dbn.zst")
                {
                    databento::DbnFileStore dbn_store{bookUpdate};
                    dbn_store.Replay(MarketDataProcessor::processQuote);
                }
            }
        };
    }

    void MarketDataHistoricalClient::stop()
    {

    }
}