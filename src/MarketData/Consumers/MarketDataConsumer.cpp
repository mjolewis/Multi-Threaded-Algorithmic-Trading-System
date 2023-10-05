//
// Created by Michael Lewis on 10/2/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_CPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_CPP

#include <thread>

#include "MarketDataConsumer.hpp"
#include "src/MarketData/Processors/MarketDataProcessor.hpp"

namespace MarketData
{
    // Overloaded ctor that initializes the consumer and accepts upstream components so that it can
    // consume data and delegate the processing to the streaming processor
    template<typename T>
    MarketDataConsumer<T>::MarketDataConsumer(const T& marketDataClient, const MarketDataProcessor& streamingProcessor)
        : marketDataClient{marketDataClient}, streamingProcessor{streamingProcessor}, stopSignal{false}
    {

    }

    // Subscribes to market data from either the historical client or live client depending on T.
    // The historical client should be used for back-testing. The live client must be used for live trading.
    // T is configurable via config.json.
    template<typename T>
    void MarketDataConsumer<T>::start()
    {
        std::thread consumerThread(marketDataClient.getBookUpdate());

        // Blocks the current thread until the thread identified by *this finishes its execution.
        if (consumerThread.joinable()) consumerThread.join();
    }

    // Stops consuming data from the publisher. Useful in scenarios where the trading system should be shut down.
    template<typename T>
    void MarketDataConsumer<T>::stop()
    {
        stopSignal = true;
    }
} // MarketData


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_CPP