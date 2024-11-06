//
// Responsible for managing orders throughout the trading day
//
// Created by Michael Lewis on 10/27/23.
//

#include <memory>
#include <unordered_map>

#include "OrderManager.hpp"
#include "../../StrategyCommon/utils/OrderUtil.hpp"

namespace BeaconTech::RiskManager
{
    OrderManager::OrderManager(const BeaconTech::Common::Logger& logger, const std::shared_ptr<Common::Clock>& clock)
        : logger{logger}, clock{clock}, openOrders{new std::unordered_map<uint32_t, Strategies::Order>()}
    {
        logger.logInfo(CLASS, "CTOR", "Creating OrderManager");
    }

    OrderManager::~OrderManager()
    {
        logger.logInfo(CLASS, "DTOR", "Destroying OrderManager");
    }

    // Creates buy and sell orders for the MarketMaker, uses the RiskManager for pre-trade risk checks,
    // and sends the orders into the market
    void OrderManager::onOrderRequest(const uint32_t& instrumentId, double bidPrice, double askPrice, uint32_t qty)
    {
        Strategies::Order buyOrder = OrderUtil::createOrder(instrumentId, clock, bidPrice, qty,
                                                            MarketData::Side::BUY, ExecType::SUBMIT,
                                                            OrderStatus::SUBMIT_PENDING);

        Strategies::Order sellOrder = OrderUtil::createOrder(instrumentId, clock, askPrice, qty,
                                                             MarketData::Side::SELL, ExecType::SUBMIT,
                                                             OrderStatus::SUBMIT_PENDING);

        // todo cancel/modify open orders if necessary, perform pre-trade risk checks in RiskManager
        //      need a SubmitHandler, ReplaceHandler, CancelHandler and will pass the order to the
        //      respective handler

        openOrders->emplace(buyOrder.clOrdId, buyOrder);
        openOrders->emplace(sellOrder.clOrdId, sellOrder);
    }
} // BeaconTech::RiskManager