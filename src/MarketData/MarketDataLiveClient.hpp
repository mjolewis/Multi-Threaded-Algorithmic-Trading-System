//
// Created by Michael Lewis on 9/29/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATALIVECLIENT_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATALIVECLIENT_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <memory>

#include <databento/live.hpp>
#include <databento/log.hpp>

#include "IMarketDataProvider.hpp"

// Forward Declarations
class MarketDataStreamingClient;

class MarketDataLiveClient : public IMarketDataProvider
{
private:
    std::shared_ptr<databento::LiveBlocking> client;
    std::shared_ptr<MarketDataStreamingClient> streamingClient;

public:
    explicit MarketDataLiveClient();
    ~MarketDataLiveClient() override = default;

    void initializeMarketDataClient() override;
    std::shared_ptr<IMarketDataProvider> getClient() const override;
    void closeClientConnection() override;
};


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATALIVECLIENT_HPP
