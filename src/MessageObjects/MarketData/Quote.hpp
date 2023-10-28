//
// Represents a resting order in the book. Quotes are normalized MBO messages received from
// the market data provider that can be consumed by downstream components in a consistent way
//
// Created by Michael Lewis on 10/6/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_QUOTE_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_QUOTE_HPP

#include <chrono>
#include <string>
#include <utility>

#include "Side.hpp"
#include "CommonServer/typesystem/DateTimes.hpp"

namespace BeaconTech::MessageObjects
{

    struct Quote
    {
        std::uint32_t instrumentId;
        BeaconTech::MessageObjects::Side side;
        double price{};
        std::uint32_t size{};
        Common::UnixNanos timestamp{};

        Quote(std::uint32_t instrumentId, BeaconTech::MessageObjects::Side side,
              double price, std::uint32_t size, Common::UnixNanos timestamp)
                : instrumentId{instrumentId}, side{std::move(side)},
                  price{price}, size{size}, timestamp{timestamp}
        {

        }
    };
} // namespace BeaconTech::MessageObjects


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_QUOTE_HPP
