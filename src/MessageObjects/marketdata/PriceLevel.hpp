//
// A representation of the order book for a given price level and the associated frequency of that level.
// For example, a bid can be represented as $25.10 x 100 with a count of 1000 to indicate that there
// are 1000 resting orders for a given instrument at this specified price x size
//
// Created by Michael Lewis on 10/6/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_PRICELEVEL_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_PRICELEVEL_HPP

#include <utility>

#include "CommonServer/types/NumericTypes.hpp"

namespace BeaconTech::MarketData
{

    struct PriceLevel
    {
        double price;
        std::uint32_t size;
        MarketData::Side side;
        unsigned int count;

        PriceLevel() : price{Common::NaN}, size{0}, side{MarketData::Side::UNKNOWN}, count{0}
        {

        }

        PriceLevel(double price, std::uint32_t size, MarketData::Side side, unsigned count)
            : price{price}, size{size}, side{std::move(side)}, count{count}
        {

        }
    };
} // namespace BeaconTech::MarketData


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_PRICELEVEL_HPP
