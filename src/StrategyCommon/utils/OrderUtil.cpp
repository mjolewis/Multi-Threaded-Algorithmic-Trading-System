//
// Common order utilities
//
// Created by Michael Lewis on 10/28/23.
//

#include <memory>

#include "OrderUtil.hpp"
#include "MessageObjects/strategies/Order.hpp"
#include "MessageObjects/strategies/ExecType.hpp"
#include "MessageObjects/strategies/OrderStatus.hpp"
#include "MessageObjects/marketdata/Side.hpp"
#include "CommonServer/utils/Clock.hpp"

namespace BeaconTech::Strategies
{
    Strategies::Order OrderUtil::createOrder(uint32_t instrumentId, const std::shared_ptr<Common::Clock>& clock,
                                             double price, uint32_t qty, const MarketData::Side& side,
                                             const ExecType& execType, const OrderStatus& orderStatus)
    {
        Strategies::Order order;
        order.execType = execType;
        order.instrumentId = instrumentId;
        order.price = price;
        order.orderStatus = orderStatus;
        order.qty = qty;
        order.side = side;
        order.tradeDate = clock->tradeDate();
        order.createTime = clock->createTime();
        order.version = 1;

        return order;
    }
} // BeaconTech::Strategies