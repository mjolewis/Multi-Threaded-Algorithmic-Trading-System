//
// Created by Michael Lewis on 10/2/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_HPP

#include "src/MarketData/Processors/MarketDataProcessor.hpp"

namespace MarketData
{
    template<typename T>
    class MarketDataConsumer
    {
    private:
        T marketDataClient;
        MarketDataProcessor streamingProcessor;
        bool stopSignal;

    public:
        MarketDataConsumer(const T& marketDataClient, const MarketDataProcessor& streamingProcessor);
        virtual ~MarketDataConsumer() = default;

        void start();
        void stop();
    };

} // MarketData


// ********** Start Template Definitions **********
#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_CPP
#include "MarketDataConsumer.cpp"
#endif //#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_CPP
// ********** End Template Definitions **********

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATACONSUMER_HPP
