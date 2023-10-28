//
// Responsible for managing orders throughout the trading day
//
// Created by Michael Lewis on 10/27/23.
//

#include <memory>
#include <unordered_map>

#include "OrderManager.hpp"
#include "MessageObjects/strategies/Order.hpp"
#include "StrategyCommon/utils/OrderUtil.hpp"
#include "MessageObjects/marketdata/Side.hpp"
#include "MessageObjects/strategies/ExecType.hpp"
#include "MessageObjects/strategies/OrderStatus.hpp"

namespace BeaconTech::Strategies
{
    OrderManager::OrderManager() : openOrders{std::unique_ptr<std::unordered_map<std::uint32_t, Strategies::Order>>()}
    {

    }

    // Creates buy and sell orders for the MarketMaker, uses the RiskManager for pre-trade risk checks,
    // and sends the orders into the market
    void OrderManager::onOrderRequest(const std::uint32_t& instrumentId, double bidPrice, double askPrice, uint32_t qty)
    {
        Strategies::Order buyOrder = OrderUtil::createOrder(instrumentId, bidPrice, qty,
                                                         MarketData::Side::BUY, ExecType::SUBMIT,
                                                         OrderStatus::SUBMIT_PENDING);

        Strategies::Order sellOrder = OrderUtil::createOrder(instrumentId, bidPrice, qty,
                                                            MarketData::Side::SELL, ExecType::SUBMIT,
                                                            OrderStatus::SUBMIT_PENDING);

        // todo have the RiskManager perform pre-trade risk checks
    }
} // BeaconTech::StrategyCommon