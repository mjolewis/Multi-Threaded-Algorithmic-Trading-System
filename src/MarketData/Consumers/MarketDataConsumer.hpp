//
// A consumer thread for inbound market data messages.
//
// Created by Michael Lewis on 10/2/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_HPP

#include <array>
#include <memory>

#include "MarketData/Processors/MarketDataProcessor.hpp"
#include "MarketData/MarketDataUtils.hpp"

namespace BeaconTech::MarketData
{
    template<typename T>
    class MarketDataConsumer
    {
    private:
        inline static constexpr int NUM_THREADS = 4;

        T marketDataClient;
        std::shared_ptr<MarketDataProcessor> streamingProcessor;
        std::array<std::thread, NUM_THREADS> consumerThreads;
        bool stopSignal;

    public:
        MarketDataConsumer() = default;
        MarketDataConsumer(const T& marketDataClient, std::shared_ptr<MarketDataProcessor>& streamingProcessor);
        MarketDataConsumer(MarketDataConsumer&& other) noexcept = default;
        virtual ~MarketDataConsumer() = default;

        MarketDataConsumer<T>& operator=(const MarketDataConsumer<T>& other);

        MarketDataConsumer<T>& operator=(MarketDataConsumer<T>&& other) noexcept;

        void start();

        void stop();
    };

} // namespace BeaconTech::MarketData


// ********** Start Template Definitions **********
#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_CPP
#include "MarketDataConsumer.cpp"
#endif //#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_CPP
// ********** End Template Definitions **********

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_HPP
