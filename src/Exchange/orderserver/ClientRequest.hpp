//
// A structure to represent information for a single order request from the client to the exchange
//
// Created by Michael Lewis on 11/17/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CLIENTREQUEST_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CLIENTREQUEST_HPP

#include <sstream>

#include "CommonServer/datastructures/ConcurrentLockFreeQueue.hpp"
#include "MessageObjects/marketdata/OrderEvent.hpp"
#include "MessageObjects/marketdata/Side.hpp"
#include "CommonServer/typesystem/NumericTypes.hpp"

namespace BeaconTech::Exchange
{

    // Directive to tightly pack the structure without extra padding.
    // Enables the structure to be sent over the network as a flat binary structure.
    #pragma pack(push, 1)

    struct ClientRequest
    {
        MarketData::OrderEvent orderEvent = MarketData::OrderEvent::INVALID;
        Common::ClientId clientId = Common::ClientId_INVALID;
        Common::TickerId tickerId = Common::TickerId_INVALID;
        Common::OrderId orderId = Common::OrderId_INVALID;
        MarketData::Side side = MarketData::Side::UNKNOWN;
        Common::Price price = Common::Price_INVALID;
        Common::Qty qty = Common::Qty_INVALID;

        auto toString() const
        {
            std::stringstream stream;
            stream << "ClientRequest ["
                   << "orderEvent=" << orderEvent.getDesc()
                   << ", clientId=" << Common::clientIdToString(clientId)
                   << ", tickerId=" << Common::tickerIdToString(tickerId)
                   << ", orderId=" << Common::orderIdToString(orderId)
                   << ", side=" << side.getDesc()
                   << ", price=" << Common::priceToString(price)
                   << ", qty=" << Common::qtyToString(qty)
                   << "]";

            return stream.str();
        }
    };

    // Only tightly pack structures sent over the network, so restore alignment to the default
    #pragma pack(pop)

    // Orders incoming to the matching engine are written to a lock free queue
    // Occurs in a separate thread from client responses so incoming orders
    // don't have to wait on any response actions
    using ClientRequestLFQueue = Common::ConcurrentLockFreeQueue<ClientRequest>;

} // BeaconTech::Exchange

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CLIENTREQUEST_HPP
