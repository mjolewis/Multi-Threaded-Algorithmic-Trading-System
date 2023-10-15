//
// Common market data aliases used throughout the system
//
// Created by Michael Lewis on 10/10/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MDTYPES_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MDTYPES_HPP

#include <memory>
#include <functional>

#include "src/MarketData/OrderBook.hpp"
#include "src/MessageObjects/MarketData/Quote.hpp"
#include "src/MessageObjects/MarketData/PriceLevel.hpp"

namespace BeaconTech
{
    using OrderBook = std::unordered_map<std::uint64_t, MessageObjects::Quote>;

    using OrderBooks = std::unordered_map<std::uint32_t, OrderBook>;

    using Bbos = std::unordered_map<std::uint32_t, std::pair<MessageObjects::PriceLevel, MessageObjects::PriceLevel>>;

//    using MdCallback = std::function<void (const std::uint32_t& instrumentId, const databento::MboMsg& msg)>;
    using MdCallback = std::function<void (const std::uint32_t& instrumentId, const std::shared_ptr<Bbos>& bbos)>;

} // namespace BeaconTech

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MDTYPES_HPP
