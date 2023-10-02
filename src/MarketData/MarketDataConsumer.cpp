//
// Created by Michael Lewis on 10/2/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_CPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_CPP

#include "MarketDataConsumer.hpp"
#include "IMarketDataProvider.hpp"
#include "MarketDataHistoricalClient.hpp"
#include "MarketDataLiveClient.hpp"

namespace MarketData
{
    template<typename T>
    MarketDataConsumer<T>::MarketDataConsumer() : marketDataClient{}, streamingProcessor{}, stopSignal{false}
    {

    }

    template<typename T>
    MarketDataConsumer<T>::MarketDataConsumer(const T& marketDataClient, const MarketDataProcessor& streamingProcessor)
        : marketDataClient{marketDataClient}, streamingProcessor{streamingProcessor}, stopSignal{false}
    {

    }

    template<typename T>
    void MarketDataConsumer<T>::start()
    {

    }

    template<typename T>
    void MarketDataConsumer<T>::stop()
    {
        stopSignal = true;
    }
} // MarketData

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_CPP