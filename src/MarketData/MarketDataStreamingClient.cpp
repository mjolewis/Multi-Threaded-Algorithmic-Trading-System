//
// Created by Michael Lewis on 9/28/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_CPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_CPP

#include "MarketDataStreamingClient.hpp"
#include "MarketDataHistoricalClient.hpp"
#include "MarketDataLiveClient.hpp"

namespace MarketData
{
    template<typename T>
    MarketDataStreamingClient<T>::MarketDataStreamingClient(const T& marketDataClient)
            : marketDataClient{marketDataClient}
    {

    }

    template<typename T>
    void MarketDataStreamingClient<T>::initialize()
    {

    }
}

#endif