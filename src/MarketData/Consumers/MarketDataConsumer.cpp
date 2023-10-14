//
// A consumer thread for inbound market data messages.
//
// Created by Michael Lewis on 10/2/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_CPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_CPP

#include <future>
#include <utility>

#include "MarketDataConsumer.hpp"
#include "MarketData/Processors/MarketDataProcessor.hpp"

namespace BeaconTech::MarketData
{
    // Overloaded ctor that initializes the consumer and accepts upstream components so that it can
    // consume data and delegate the processing to the streaming processor
    template<typename T>
    MarketDataConsumer<T>::MarketDataConsumer(const T& marketDataClient, std::shared_ptr<MarketDataProcessor>& streamingProcessor)
        : stopSignal{false}
    {
        this->marketDataClient = marketDataClient;
        this->streamingProcessor = streamingProcessor;
    }

    template<typename T>
    MarketDataConsumer<T>& MarketDataConsumer<T>::operator=(const MarketDataConsumer<T>& other)
    {
        // Avoid self-assigment
        if (this == &other) return *this;

        marketDataClient = other.marketDataClient;
        streamingProcessor = other.streamingProcessor;
        consumerThreads = other.consumerThreads;
        stopSignal = other.stopSignal;

        return *this;
    }

    template<typename T>
    MarketDataConsumer<T>& MarketDataConsumer<T>::operator=(MarketDataConsumer<T>&& other) noexcept
{
        // Avoid self-assigment
        if (this == &other) return *this;

        marketDataClient = std::move(other.marketDataClient);
        streamingProcessor = std::move(other.streamingProcessor);
        consumerThreads = std::move(other.consumerThreads);
        stopSignal = std::move(other.stopSignal);

        return *this;
    }

    // Subscribes to market data from either the historical client or live client depending on T.
    // The historical client should be used for back-testing. The live client must be used for live trading.
    // T is configurable via config.json.
    template<typename T>
    void MarketDataConsumer<T>::start()
    {
        // Note - The destructor of the std::future will block at the end of the full expression
        // until the asynchronous operation completes. As a result, we use a lvalue expression
        // whose lifetime is bound to the variable
        auto future = std::async(std::launch::async, marketDataClient.getBookUpdate(streamingProcessor));
    }

    // Disconnects the session gateway
    template<typename T>
    void MarketDataConsumer<T>::stop()
    {
        stopSignal = true;
        marketDataClient.stop();
    }
} // namespace BeaconTech::MarketData


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_CPP