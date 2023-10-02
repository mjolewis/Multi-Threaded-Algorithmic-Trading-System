//
// Created by Michael Lewis on 9/29/23.
//

#include <memory>

#include <databento/live.hpp>
#include <databento/log.hpp>

#include "MarketDataLiveClient.hpp"
#include "MarketDataStreamingClient.hpp"
#include "MarketDataUtils.hpp"

namespace MarketData
{
    MarketDataLiveClient::MarketDataLiveClient() : IMarketDataProvider{}, client{}
    {
        streamingClient = std::make_shared<MarketDataStreamingClient<MarketDataLiveClient>>(*this);
        initialize();
    }

    void MarketDataLiveClient::initializeMarketDataClient()
    {
        client = std::make_shared<databento::LiveBlocking>(MarketDataUtils::getLiveClient());

        streamingClient->initialize();
    }

    std::shared_ptr<IMarketDataProvider> MarketDataLiveClient::getClient() const
    {
        return std::make_shared<MarketDataLiveClient>(*this);
    }

    void MarketDataLiveClient::closeClientConnection()
    {
        client->Stop();
    }
}