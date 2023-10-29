//
// Common order utilities
//
// Created by Michael Lewis on 10/28/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERUTIL_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERUTIL_HPP

#include <memory>

#include "MessageObjects/strategies/Order.hpp"
#include "MessageObjects/strategies/ExecType.hpp"
#include "MessageObjects/strategies/OrderStatus.hpp"
#include "MessageObjects/marketdata/Side.hpp"
#include "CommonServer/utils/Clock.hpp"

namespace BeaconTech::Strategies
{

    class OrderUtil
    {
    public:
        static Strategies::Order createOrder(uint32_t instrumentId, const std::shared_ptr<Common::Clock>& clock,
                                             double price, uint32_t qty, const MarketData::Side& side,
                                             const ExecType& execType, const OrderStatus& orderStatus);
    };

} // BeaconTech::Strategies

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERUTIL_HPP
