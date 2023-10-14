//
// Created by Michael Lewis on 10/10/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_BTCONCEPTS_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_BTCONCEPTS_HPP

#include <concepts>

namespace BeaconTech
{
    // Concept to enforce compile-time validation of a mbbo consumed from the market data provider
    template<typename T>
    concept Mbbo = requires(const T& mbbo)
    {
        mbbo.hd.instrument_id;
        mbbo.hd.ts_event;
        mbbo.action;
        mbbo.side;
        mbbo.order_id;
        mbbo.price;
        mbbo.size;
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
}

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_BTCONCEPTS_HPP
