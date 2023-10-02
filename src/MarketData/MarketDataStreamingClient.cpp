//
// Created by Michael Lewis on 9/28/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_CPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_CPP

#include "MarketDataStreamingClient.hpp"
#include "MarketDataHistoricalClient.hpp"
#include "MarketDataLiveClient.hpp"
#include "MarketDataProcessor.hpp"
#include "MarketDataConsumer.hpp"

namespace MarketData
{
    template<typename T>
    MarketDataStreamingClient<T>::MarketDataStreamingClient(const T& marketDataClient)
            : marketDataClient{marketDataClient}, streamingProcessor{},
            streamingConsumer{marketDataClient, streamingProcessor}
    {
        createStreamingProcessor();
        streamingConsumer = MarketDataConsumer<T>{marketDataClient, streamingProcessor};
    }

    template<typename T>
    void MarketDataStreamingClient<T>::createStreamingProcessor()
    {
        // Will eventually support multiple types of processor to handle regional data (e.g. US + CA + EU + etc.)
        streamingProcessor = MarketDataProcessor{};
    }

    template<typename T>
    void MarketDataStreamingClient<T>::initialize()
    {
        streamingProcessor.initialize();
        streamingConsumer.start();
    }
}

#endif