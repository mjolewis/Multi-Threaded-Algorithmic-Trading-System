//
// Responsible for managing orders throughout the trading day
//
// Created by Michael Lewis on 10/27/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERMANAGER_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERMANAGER_HPP

#include <memory>
#include <unordered_map>

#include "../../MessageObjects/strategies/Order.hpp"
#include "../../CommonServer/utils/Clock.hpp"
#include "../../CommonServer/logging/Logger.hpp"

namespace BeaconTech::Strategies
{
    class OrderManager
    {
    private:
        inline static const std::string CLASS = "OrderManager";

        // Management properties
        const BeaconTech::Common::Logger& logger;
        const std::shared_ptr<Common::Clock>& clock;

        // Order properties
        std::unordered_map<uint32_t, Strategies::Order>* openOrders; // instrumentId -> order

    public:
        OrderManager(const BeaconTech::Common::Logger& logger, const std::shared_ptr<Common::Clock>& clock);

        virtual ~OrderManager();

        void onOrderRequest(const uint32_t& instrumentId, double bidPrice, double askPrice, uint32_t qty);

        // Deleted default ctors and assignment operators
        OrderManager(const OrderManager& other) = delete;

        OrderManager(OrderManager&& other) = delete;

        OrderManager& operator=(const OrderManager& other) = delete;

        OrderManager& operator=(OrderManager&& other) = delete;
    };

} // BeaconTech::Strategies

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERMANAGER_HPP
