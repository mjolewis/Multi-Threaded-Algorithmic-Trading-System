//
// Created by Michael Lewis on 9/26/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAHISTORICALCLIENT_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAHISTORICALCLIENT_HPP

#include <iostream>
#include <string>
#include <memory>

#include <databento/historical.hpp>
#include <databento/log.hpp>

#include "IMarketDataProvider.hpp"
#include "MarketDataStreamingClient.hpp"

namespace MarketData
{
    // Forward Declarations
    class MarketDataHistoricalClient;

    template<typename T>
    class MarketDataStreamingClient;

    class MarketDataHistoricalClient : public IMarketDataProvider
    {
    private:
        std::shared_ptr<databento::Historical> client;
        std::shared_ptr<MarketDataStreamingClient<MarketDataHistoricalClient>> streamingClient;

    public:
        MarketDataHistoricalClient();
        ~MarketDataHistoricalClient() override = default;

        void initializeMarketDataClient() override;
        std::shared_ptr<IMarketDataProvider> getClient() const override;
        void closeClientConnection() override;
    };
}

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAHISTORICALCLIENT_HPP
