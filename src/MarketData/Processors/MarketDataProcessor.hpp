//
// Created by Michael Lewis on 10/2/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAPROCESSOR_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAPROCESSOR_HPP

#include <databento/timeseries.hpp>

// Concept to enforce compile-time validation of a quote consumed from the market data provider
template<typename T>
concept Quote = requires(const T& quote)
{
    quote.hd.instrument_id;
    quote.hd.ts_event;
    quote.action;
    quote.side;
    quote.order_id;
    quote.price;
    quote.size;
};

// Concept to enforce compile-time validation of a trade consumed from the market data provider
template<typename T>
concept Trade = requires(const T& trade)
{
    trade.hd.instrument_id;
    trade.hd.ts_event;
    trade.action;
    trade.price;
    trade.depth;
    trade.side;
    trade.size;
};

namespace MarketData
{
    class MarketDataProcessor
    {
    public:
        MarketDataProcessor() = default;
        virtual ~MarketDataProcessor() = default;

        void initialize();

        // Book Updates
        template<typename T>
        requires Quote<T>
        static void handle(const T& quote);

        template<typename T>
        requires Trade<T>
        static void handle(const T& trade);

        static databento::KeepGoing processBookUpdate(const databento::Record& record);
    };
}


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAPROCESSOR_HPP
