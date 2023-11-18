//
// Created by Michael Lewis on 10/25/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_NUMERICTYPES_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_NUMERICTYPES_HPP

#include <limits>
#include <string>

namespace BeaconTech::Common
{
    constexpr auto NaN = std::numeric_limits<double>::quiet_NaN();

    // Order identifier
    using OrderId = std::uint64_t;
    constexpr auto OrderId_INVALID = std::numeric_limits<OrderId>::max();
    inline auto orderIdToString(OrderId orderId) -> std::string
    {
        if (orderId == OrderId_INVALID) return "INVALID";
        else return std::to_string(orderId);
    }

    // Trading instrument id
    using TickerId = std::uint32_t;
    constexpr auto TickerId_INVALID = std::numeric_limits<TickerId>::max();
    inline auto tickerIdToString(TickerId tickerId) -> std::string
    {
        if (tickerId == TickerId_INVALID) return "INVALID";
        else return std::to_string(tickerId);
    }

    // Used by matching engine simulator
    using ClientId = std::uint32_t;
    constexpr auto ClientId_INVALID = std::numeric_limits<ClientId>::max();
    inline auto clientIdToString(ClientId clientId) -> std::string
    {
        if (clientId == ClientId_INVALID) return "INVALID";
        else return std::to_string(clientId);
    }

    // Order price
    using Price = std::int64_t;
    constexpr auto Price_INVALID = std::numeric_limits<Price>::max();
    inline auto priceToString(Price price) -> std::string
    {
        if (price == Price_INVALID) return "INVALID";
        else return std::to_string(price);
    }

    // Order quantity
    using Qty = std::uint32_t;
    const auto Qty_INVALID = std::numeric_limits<Qty>::max();
    inline auto qtyToString(Qty qty) -> std::string
    {
        if (qty == Qty_INVALID) return "INVALID";
        else return std::to_string(qty);
    }

    // Queue position
    using Priority = std::uint64_t;
    const auto Priority_INVALID = std::numeric_limits<Priority>::max();
    inline auto priorityToString(Priority priority) -> std::string
    {
        if (priority == Priority_INVALID) return "INVALID";
        else return std::to_string(priority);
    }


} // namespace BeaconTech::Common

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_NUMERICTYPES_HPP
