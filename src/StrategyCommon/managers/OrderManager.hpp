//
// Created by Michael Lewis on 10/27/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERMANAGER_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERMANAGER_HPP

namespace BeaconTech
{

    class OrderManager
    {
    public:
        OrderManager() = default;

        virtual ~OrderManager() = default;

        // Deleted default ctors and assignment operators
        OrderManager(const OrderManager& other) = delete;

        OrderManager(OrderManager&& other) = delete;

        OrderManager& operator=(const OrderManager& other) = delete;

        OrderManager& operator=(OrderManager&& other) = delete;
    };

} // BeaconTech

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERMANAGER_HPP
