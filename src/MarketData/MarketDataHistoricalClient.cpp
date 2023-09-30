//
// Created by Michael Lewis on 9/28/23.
//

#include <memory>

#include <databento/historical.hpp>
#include <databento/fixed_price.hpp>

#include "MarketDataHistoricalClient.hpp"
#include "MarketDataStreamingClient.hpp"
#include "MarketDataUtils.hpp"

using namespace databento;

KeepGoing processQuote(const Record& record)
{
    auto mboMsg = record.Get<MboMsg>();
    auto size = mboMsg.size;
    auto price = float(mboMsg.price) / float(databento::kFixedPriceScale);
    auto side = mboMsg.side;
    std::cout << mboMsg.hd.instrument_id << '\t' << size << '\t' << price << '\t' << side << '\n';
    return KeepGoing::Continue;
}

MarketDataHistoricalClient::MarketDataHistoricalClient() : IMarketDataProvider{}, client{}
{
    initialize();
}

void MarketDataHistoricalClient::initializeConnectionToMarketDataProvider()
{
    client = std::make_shared<databento::Historical>(MarketDataUtils::getHistoricalClient());

    auto downloaded_files = client->BatchDownload(ConfigReader::extractStringValueFromConfig("marketData"),
                                                       ConfigReader::extractStringValueFromConfig("fileToDownload"));

    for (const auto& file : downloaded_files)
    {
        if (file.substr(file.length() - 8) == ".dbn.zst")
        {
            DbnFileStore dbn_store{file};
            dbn_store.Replay(processQuote);
        }
    }

    streamingClient->initialize();
}

std::shared_ptr<IMarketDataProvider> MarketDataHistoricalClient::getClient() const
{
    return std::make_shared<MarketDataHistoricalClient>(*this);
}

void MarketDataHistoricalClient::closeClientConnection()
{

}