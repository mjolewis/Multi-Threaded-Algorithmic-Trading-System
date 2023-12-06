//
// Common market data aliases used throughout the system
//
// Created by Michael Lewis on 10/10/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MDTYPES_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MDTYPES_HPP

#include <memory>
#include <functional>

#include "MarketData/OrderBook.hpp"
#include "MessageObjects/marketdata/Quote.hpp"
#include "MessageObjects/marketdata/PriceLevel.hpp"

namespace BeaconTech::Common
{
    // key = orderId -> quote
    using OrderBook = std::unordered_map<std::uint64_t, MarketData::Quote>;

    // key = instrumentId -> OrderBook
    using OrderBooks = std::unordered_map<std::uint32_t, OrderBook>;

    // instrumentId, Bid, Ask
    using Bbo = std::tuple<std::uint32_t, MarketData::PriceLevel, MarketData::PriceLevel>;

    // key = instrumentId -> std::tuple<instrumentId, bid, ask>
    using Bbos = std::unordered_map<std::uint32_t, Bbo>;

    using MdCallback = std::function<void (const std::uint32_t& instrumentId,
                                           const MarketData::Quote& quote,
                                           const Bbo& bbo)>;

} // namespace BeaconTech::Common

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MDTYPES_HPP
