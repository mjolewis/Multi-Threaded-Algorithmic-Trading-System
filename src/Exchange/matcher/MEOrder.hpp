//
// Represents a single order in the order book
//
// Created by Michael Lewis on 11/18/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MEORDER_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MEORDER_HPP

#include <array>
#include <sstream>

#include "CommonServer/types/NumericTypes.hpp"
#include "MessageObjects/marketdata/Side.hpp"

namespace BeaconTech::Exchange
{

    struct MEOrder
    {
        Common::TickerId tickerId = Common::TickerId_INVALID;
        Common::ClientId clientId = Common::ClientId_INVALID;
        Common::OrderId clOrdId = Common::OrderId_INVALID;
        Common::OrderId marketOrderId = Common::OrderId_INVALID;
        MarketData::Side side = MarketData::Side::UNKNOWN;
        Common::Price price = Common::Price_INVALID;
        Common::Qty qty = Common::Qty_INVALID;
        Common::Priority priority = Common::Priority_INVALID;

        // Pointers to orders in a doubly linked list at a given price level
        // All orders at this price level are arranged in FIFO order
        MEOrder* prevOrder = nullptr;
        MEOrder* nextOrder = nullptr;

        auto toString() const
        {
            std::stringstream stream;
            stream << "MatchingEngineOrder ["
                   << ", tickerId=" << Common::tickerIdToString(tickerId)
                   << ", clientId=" << Common::clientIdToString(clientId)
                   << ", clOrdId=" << Common::orderIdToString(clOrdId)
                   << ", marketOrderId=" << Common::orderIdToString(marketOrderId)
                   << ", side=" << side.getDesc()
                   << ", price=" << Common::priceToString(price)
                   << ", qty=" << Common::qtyToString(qty)
                   << ", priority=" << Common::priorityToString(priority)
                   << "]";

            return stream.str();
        }
    };

    using Orders = std::array<MEOrder*, Common::ME_MAX_ORDER_IDS>;
    using ClientIdToOrders = std::array<Orders, Common::ME_MAX_NUM_CLIENTS>;

} //namespace BeaconTech::Exchange

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MEORDER_HPP
