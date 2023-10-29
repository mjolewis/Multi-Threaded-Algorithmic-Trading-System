//
// Responsible for managing orders throughout the trading day
//
// Created by Michael Lewis on 10/27/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERMANAGER_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERMANAGER_HPP

#include <cstdint>
#include <memory>
#include <unordered_map>

#include "MessageObjects/strategies/Order.hpp"
#include "CommonServer/utils/Clock.hpp"

namespace BeaconTech::Strategies
{

    class OrderManager
    {
    private:
        const std::shared_ptr<Common::Clock>& clock;
        std::unique_ptr<std::unordered_map<uint32_t, Strategies::Order>> openOrders; // instrumentId -> order

    public:
        OrderManager(const std::shared_ptr<Common::Clock>& clock);

        virtual ~OrderManager() = default;

        void onOrderRequest(const uint32_t& instrumentId, double bidPrice, double askPrice, uint32_t qty);

        // Deleted default ctors and assignment operators
        OrderManager(const OrderManager& other) = delete;

        OrderManager(OrderManager&& other) = delete;

        OrderManager& operator=(const OrderManager& other) = delete;

        OrderManager& operator=(OrderManager&& other) = delete;
    };

} // BeaconTech::Strategies

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERMANAGER_HPP
