//
// A consumer thread for inbound market data messages.
//
// Created by Michael Lewis on 10/2/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_CPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_CPP

#include <future>

#include "MarketDataConsumer.hpp"
#include "MarketData/processors/MarketDataProcessor.hpp"

namespace BeaconTech::MarketData
{
    // Overloaded ctor that initializes the consumer and accepts upstream components so that it can
    // consume data and delegate the processing to the streaming processor
    template<typename T>
    MarketDataConsumer<T>::MarketDataConsumer(std::shared_ptr<MarketDataProcessor> streamingProcessor)
        : stopSignal{false}
    {
        this->streamingProcessor = streamingProcessor;
    }

    // Subscribes to market data from either the historical client or live client depending on T.
    // The historical client should be used for back-testing. The live client must be used for live trading.
    // T is configurable via config.json.
    template<typename T>
    void MarketDataConsumer<T>::start(std::shared_ptr<T> marketDataClient_)
    {
        this->marketDataClient = marketDataClient_;
        // Note - The destructor of the std::future will block at the end of the full expression
        // until the asynchronous operation completes. As a result, we use a lvalue expression
        // whose lifetime is bound to the variable
        auto future = std::async(std::launch::async, marketDataClient->getBookUpdate(streamingProcessor));
    }

    // Disconnects the session gateway
    template<typename T>
    void MarketDataConsumer<T>::stop()
    {
        stopSignal = true;
    }
} // namespace BeaconTech::MarketData


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_CPP