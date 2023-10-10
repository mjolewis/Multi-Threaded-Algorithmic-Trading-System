//
// Created by Michael Lewis on 10/4/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYSERVER_CPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYSERVER_CPP

#include "StrategyServer.hpp"
#include "StrategyEngine.hpp"
#include "CommonServer/Utils/ConfigManager.hpp"

namespace BeaconTech::Strategies
{

    // Order of instantiation matters. The Server and Engines should be instantiated before the Market Data Client
    // to ensure that these components are ready to start processing data published by the Client.
    template<typename T>
    StrategyServer<T>::StrategyServer() : numThreads{Utils::ConfigManager::intConfigValueDefaultIfNull("numThreads", 1)}
    {
        createThreads();
        marketDataClient = T{"StrategyServer"};
    }

    // Create the Engine threads. The number of engines is configurable and is used to partition the system
    // by symbol ranges to improve latency and throughput.
    template<typename T>
    void StrategyServer<T>::createThreads()
    {
        for (int thread = 0; thread < numThreads; ++thread)
        {
            strategyEngines.emplace_back(*this, thread);
        }
    }
} // namespace BeaconTech::Strategies


#endif