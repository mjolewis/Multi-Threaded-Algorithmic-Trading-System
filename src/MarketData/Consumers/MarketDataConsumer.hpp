//
// @Note - This Consumer is not CopyConstructible, CopyAssignable, or MoveAssignable.
// It is, however, MoveConstructible to comply with the std::thread protocol.
//
// Created by Michael Lewis on 10/2/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_HPP

#include <array>

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
        MarketDataProcessor streamingProcessor;
        std::array<std::thread, NUM_THREADS> consumerThreads;
        bool stopSignal;

    public:
        MarketDataConsumer(const T& marketDataClient, const MarketDataProcessor& streamingProcessor);
        MarketDataConsumer(MarketDataConsumer&& other) noexcept = default;
        virtual ~MarketDataConsumer() = default;

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
