//
// A consumer thread for inbound market data messages.
//
// Created by Michael Lewis on 10/2/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_HPP

#include <array>
#include <memory>

#include "MarketData/processors/MarketDataProcessor.hpp"
#include "MarketData/MarketDataUtils.hpp"

namespace BeaconTech::MarketData
{
    template<typename T>
    class MarketDataConsumer
    {
    private:
        inline static constexpr int NUM_THREADS = 4;

        std::shared_ptr<T> marketDataClient;
        std::shared_ptr<MarketDataProcessor> streamingProcessor;
        std::array<std::thread, NUM_THREADS> consumerThreads;
        bool stopSignal;

    public:
        explicit MarketDataConsumer(std::shared_ptr<MarketDataProcessor> streamingProcessor);

        virtual ~MarketDataConsumer() = default;

        void start(std::shared_ptr<T> marketDataClient);

        void stop();

        // Deleted default ctors and assignment operators
        MarketDataConsumer() = delete;

        MarketDataConsumer(const MarketDataConsumer<T>& other) = delete;

        MarketDataConsumer(MarketDataConsumer<T>&& other) = delete;

        MarketDataConsumer<T>& operator=(const MarketDataConsumer<T>& other) = delete;

        MarketDataConsumer<T>& operator=(MarketDataConsumer<T>&& other) = delete;
    };

} // namespace BeaconTech::marketdata


// ********** Start Template Definitions **********
#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_CPP
#include "MarketDataConsumer.cpp"
#endif //#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_CPP
// ********** End Template Definitions **********

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_HPP
