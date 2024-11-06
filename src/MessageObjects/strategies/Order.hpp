//
// A data structure to represent an order that is sent into the market
//
// Created by Michael Lewis on 10/28/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDER_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDER_HPP

#include <cstdint>

#include "../marketdata/Side.hpp"
#include "ExecType.hpp"
#include "OrderStatus.hpp"
#include "../../CommonServer/types/DateTimes.hpp"

namespace BeaconTech::Strategies
{

    struct Order
    {
        int64_t clOrdId{};  // todo need to build a number generator. Format <ProcId_TradeDate_9 slots for order counter>
        Common::TimePoint createTime{};
        ExecType execType{ExecType::UNKNOWN};
        uint32_t instrumentId{0};
        Common::TimePoint lastModTime{};
        double price{0};
        OrderStatus orderStatus{OrderStatus::UNKNOWN};
        uint32_t qty{0};
        MarketData::Side side{MarketData::Side::UNKNOWN};
        Common::TradeDate tradeDate{};
        int32_t version{0};
    };
}

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDER_HPP
