//
// A data structure to represent an order that is sent into the market
//
// Created by Michael Lewis on 10/28/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDER_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDER_HPP

#include <cstdint>

#include "marketdata/Side.hpp"
#include "ExecType.hpp"
#include "OrderStatus.hpp"
#include "CommonServer/typesystem/DateTimes.hpp"

namespace BeaconTech::Strategies
{

    struct Order
    {
        uint32_t createTime{0};
        ExecType execType{ExecType::UNKNOWN};
        uint32_t instrumentId{0};
        double price{0};
        OrderStatus orderStatus{OrderStatus::UNKNOWN};
        uint32_t qty{0};
        MarketData::Side side{MarketData::Side::UNKNOWN};
        uint32_t tradeDate{0};
        int32_t version{0};
    };
}

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDER_HPP
