//
// Created by Michael Lewis on 9/29/23.
//

#include <memory>

#include <databento/live.hpp>
#include <databento/log.hpp>

#include "MarketDataLiveClient.hpp"
#include "MarketDataStreamingClient.hpp"
#include "MarketDataUtils.hpp"

MarketDataLiveClient::MarketDataLiveClient() : IMarketDataProvider{}, client{}
{
    initialize();
}

void MarketDataLiveClient::initializeConnectionToMarketDataProvider()
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