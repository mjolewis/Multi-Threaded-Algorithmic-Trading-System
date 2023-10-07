//
// Processes binary encoded market data from the provider and transforms it into a common format
// for consumption by  downstream components
//
// Created by Michael Lewis on 10/2/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAPROCESSOR_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAPROCESSOR_HPP

#include <databento/timeseries.hpp>

#include "MessageObjects/MarketData/OrderBook/Book.hpp"

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

namespace BeaconTech::MarketData
{
    class MarketDataProcessor
    {
    private:
        MessageObjects::Book orderBook;

    public:
        MarketDataProcessor();
        virtual ~MarketDataProcessor() = default;

        void initialize();

        // Book Updates
        template<typename T>
        requires Quote<T>
        void handle(const T& quote);

        template<typename T>
        requires Trade<T>
        void handle(const T& trade);

        databento::KeepGoing processBookUpdate(const databento::Record& record);
    };
} // namespace BeaconTech::MarketData


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAPROCESSOR_HPP
