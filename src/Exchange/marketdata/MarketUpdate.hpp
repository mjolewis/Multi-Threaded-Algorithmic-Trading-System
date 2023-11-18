//
// A structure to represent and publish market data updates from the matching engine
//
// Created by Michael Lewis on 11/18/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETUPDATE_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETUPDATE_HPP

#include <sstream>

#include "MessageObjects/marketdata/OrderBookAction.hpp"
#include "MessageObjects/marketdata/Side.hpp"
#include "CommonServer/typesystem/NumericTypes.hpp"
#include "CommonServer/datastructures/ConcurrentLockFreeQueue.hpp"

namespace BeaconTech::MarketData
{

// Directive to tightly pack the structure without extra padding.
// Enables the structure to be sent over the network as a flat binary structure.
#pragma pack(push, 1)

    struct MarketUpdate
    {
        MarketData::OrderBookAction action = MarketData::OrderBookAction::INVALID;
        Common::OrderId orderId = Common::OrderId_INVALID;
        Common::TickerId tickerId = Common::TickerId_INVALID;
        MarketData::Side side = MarketData::Side::UNKNOWN;
        Common::Price price = Common::Price_INVALID;
        Common::Qty qty = Common::Qty_INVALID;
        Common::Priority priority = Common::Priority_INVALID;

        auto toString() const
        {
            std::stringstream stream;
            stream << "MatchingEngineMarketUpdate ["
                   << " action=" << action.getDesc()
                   << ", orderId=" << Common::orderIdToString(orderId)
                   << ", tickerId=" << Common::tickerIdToString(tickerId)
                   << ", side=" << side.getDesc()
                   << ", price=" << Common::priceToString(price)
                   << ", qty=" << Common::qtyToString(qty)
                   << ", priority=" << Common::priorityToString(priority)
                   << "]";

            return stream.str();
        }
    };

// Only tightly pack structures sent over the network, so restore alignment to the default
#pragma pack(pop)

    using MarketUpdateLFQueue = Common::ConcurrentLockFreeQueue<MarketUpdate>;
}

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETUPDATE_HPP
