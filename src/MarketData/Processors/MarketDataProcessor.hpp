//
// Created by Michael Lewis on 10/2/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAPROCESSOR_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAPROCESSOR_HPP

#include <databento/timeseries.hpp>

namespace MarketData
{
    class MarketDataProcessor
    {
    public:
        MarketDataProcessor() = default;
        virtual ~MarketDataProcessor() = default;

        void initialize();
        static databento::KeepGoing processQuote(const databento::Record& record);
    };
}


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAPROCESSOR_HPP
