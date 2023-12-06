//
// A structure to represent information for a single order response from the exchange to the client
//
// Created by Michael Lewis on 11/17/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MECLIENTRESPONSE_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MECLIENTRESPONSE_HPP

#include <sstream>

#include "MessageObjects/marketdata/OrderEvent.hpp"
#include "MessageObjects/marketdata/Side.hpp"
#include "CommonServer/typesystem/NumericTypes.hpp"
#include "CommonServer/datastructures/ConcurrentLockFreeQueue.hpp"

namespace BeaconTech::Exchange
{

// Directive to tightly pack the structure without extra padding.
// Enables the structure to be sent over the network as a flat binary structure.
#pragma pack(push, 1)

    struct MEClientResponse
    {
        MarketData::OrderEvent orderEvent = MarketData::OrderEvent::INVALID;
        Common::ClientId clientId = Common::ClientId_INVALID;
        Common::TickerId tickerId = Common::TickerId_INVALID;
        Common::OrderId clOrdId = Common::OrderId_INVALID; // Client order identifier
        Common::OrderId marketOrderId = Common::OrderId_INVALID; // Public identifier use in market data stream
        MarketData::Side side = MarketData::Side::UNKNOWN;
        Common::Price price = Common::Price_INVALID;
        Common::Qty execQty = Common::Qty_INVALID;
        Common::Qty leavesQty = Common::Qty_INVALID;

        auto toString() const
        {
            std::stringstream stream;
            stream << "MatchingEngineClientResponse ["
                   << "orderEvent=" << orderEvent.getDesc()
                   << ", clientId=" << Common::clientIdToString(clientId)
                   << ", tickerId=" << Common::tickerIdToString(tickerId)
                   << ", clOrdId=" << Common::orderIdToString(clOrdId)
                   << ", marketOrderId=" << Common::orderIdToString(marketOrderId)
                   << ", side=" << side.getDesc()
                   << ", price=" << Common::priceToString(price)
                   << ", execQty=" << Common::qtyToString(execQty)
                   << ", leavesQty=" << Common::qtyToString(leavesQty)
                   << "]";

            return stream.str();
        }
    };

// Only tightly pack structures sent over the network, so restore alignment to the default
#pragma pack(pop)

    using ClientResponseLFQueue = Common::ConcurrentLockFreeQueue<MEClientResponse>;

} //namespace BeaconTech::Exchange

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MECLIENTRESPONSE_HPP
