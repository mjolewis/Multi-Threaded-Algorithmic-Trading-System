//
// The main entry point for all downstream business logic. The server is responsible
// for creating engines and facilitating the handoff between inbound data and the
// deterministic message processing queue that feeds the engines
//
// Created by Michael Lewis on 10/4/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYSERVER_CPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYSERVER_CPP

#include <iostream>
#include <memory>

#include "StrategyServer.hpp"
#include "StrategyEngine.hpp"
#include "CommonServer/Utils/ConfigManager.hpp"
#include "CommonServer/Utils/MdTypes.hpp"
#include "src/CommonServer/DataStructures/ConcurrentQueueProcessor.hpp"

namespace BeaconTech::Strategies
{

    // Order of instantiation matters. The Client, Server, and Engines
    // should be created before subscribing to market data
    template<typename T>
    StrategyServer<T>::StrategyServer()
        : numEngineThreads{Common::ConfigManager::intConfigValueDefaultIfNull("numEngineThreads", 1)},
          numListeners{Common::ConfigManager::intConfigValueDefaultIfNull("numListeners", 1)},
          marketDataClient{"StrategyServer"}
    {
        createThreads();
        subscribeToMarketData();
    }

    // Creates the engines and listener. The number of threads is configurable to partition the
    // system by symbol ranges (improves latency and throughput). Each thread can be also
    // configured to have multiple listeners. The typical use case is to have one engine thread
    // to ensure sequencing of each engine. Any additional listener should only be used for logging.
    template<typename T>
    void StrategyServer<T>::createThreads()
    {
        for (int thread = 0; thread < numEngineThreads; ++thread)
        {
            // When numListeners > numEngineThreads, the extra threads should be used for logging
            for (int listenerId = 0; listenerId < (numListeners / numEngineThreads); ++listenerId)
            {
                strategyEngines.emplace_back(std::make_shared<StrategyServer<T>>(*this), thread);
            }

            queueProcessors.emplace_back(std::make_shared<Common::ConcurrentQueueProcessor>(thread));
        }
    }

    // Finds the positive modulo of the instrumentId and the number of engine threads
    // and returns the engine at the associated index
    template<typename T>
    int StrategyServer<T>::getEngineThread(const std::uint32_t &instrumentId) const
    {
        return (instrumentId % numEngineThreads + numEngineThreads) % numEngineThreads;
    }

    // Schedules entities into a concurrent queue. The entity is scheduled onto
    // the thread in the thread pool associated with engineThreadId
    template<typename T>
    void StrategyServer<T>::scheduleJob(int engineThreadId, const std::shared_ptr<Common::Bbos>& bbos)
    {
        queueProcessors.at(engineThreadId)->enqueue([&]() { strategyEngines.at(engineThreadId).handle(bbos); });
    }

    // Subscribes this Strategy to market data by creating a callback that the
    // market data streaming processor uses to schedule entities into the strategy engine
    template<typename T>
    void StrategyServer<T>::subscribeToMarketData()
    {
        callback = [&](const std::uint32_t& instrumentId, const std::shared_ptr<Common::Bbos>& bbos) -> void {
            try
            {
                scheduleJob(getEngineThread(instrumentId), bbos);
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << std::endl;
            }
        };

        marketDataClient.subscribe(callback);
    }

} // namespace BeaconTech::Strategies


#endif