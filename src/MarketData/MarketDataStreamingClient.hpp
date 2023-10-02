//
// Created by Michael Lewis on 9/28/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_HPP

#include "memory"

#include "IMarketDataProvider.hpp"
#include "MarketDataHistoricalClient.hpp"
#include "MarketDataLiveClient.hpp"

namespace MarketData
{
    template<typename T>
    class MarketDataStreamingClient
    {
    private:
        T marketDataClient;

    public:
        MarketDataStreamingClient(const T& marketDataClient);
        virtual ~MarketDataStreamingClient() = default;

        void initialize();
    };
}

// ********** Start Template Definitions **********

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_CPP
#include "MarketDataStreamingClient.cpp"
#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_CPP

// ********** End Template Definitions **********

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_HPP
