//
// Represents price levels in the order book
// Maintains links to the previous and next price levels
//
// Created by Michael Lewis on 11/21/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MEORDERSATPRICE_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MEORDERSATPRICE_HPP

#include <sstream>
#include <array>

#include "MessageObjects/marketdata/PriceLevel.hpp"
#include "MEOrder.hpp"
#include "CommonServer/types/NumericTypes.hpp"

namespace BeaconTech::Exchange
{

    struct MEOrdersAtPrice
    {
        MarketData::PriceLevel priceLevel;
        MEOrder* headMEOrder = nullptr; // Pointer to the highest priority order at this price level
        MEOrdersAtPrice* prevPriceLevel = nullptr; // Pointer to more aggressive price level
        MEOrdersAtPrice* nextPriceLevel = nullptr; // Pointer to less aggressive price level

        auto toString() const
        {
            std::stringstream stream;
            stream << "MEOrdersAtPrice ["
                   << "side=" << priceLevel.side
                   << ", price=" priceLevel.price
                   << ", first order at level=" << (headMEOrder ? headMEOrder.toString() : "null")
                   << ", prev price level=" << (prevPriceLevel ? prevPriceLevel.toString() : "null")
                   << ", next price level=" << (nextPriceLevel ? nextPriceLevel.toString() : "null")
                   << "]";

            return stream.str();
        }
    };

    using OrdersAtPrice = std::array<MEOrdersAtPrice*, Common::ME_MAX_PRICE_LEVELS>;

} // BeaconTech::Exchange

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MEORDERSATPRICE_HPP
