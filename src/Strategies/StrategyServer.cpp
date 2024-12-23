//
// The main entry point for all downstream business logic. The server is responsible
// for creating engines and facilitating the handoff between inbound data and the
// deterministic message processing queue that feeds the engines
//
// Created by Michael Lewis on 10/4/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYSERVER_CPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYSERVER_CPP

#include <exception>
#include <memory>

#include "StrategyServer.hpp"

namespace BeaconTech::Strategies
{
    template<typename T>
    StrategyServer<T>::StrategyServer()
        : logger{CLASS_PATH, APP_NAME, 0},
          numEngineThreads{Common::ConfigManager::intConfigValueDefaultIfNull("numEngineThreads", 1)},
          numListeners{Common::ConfigManager::intConfigValueDefaultIfNull("numListeners", 1)},
          marketDataClient{APP_NAME, logger}
    {
        logger.logInfo(CLASS, "CTOR", "Creating StrategyServer");

        createThreads();
        subscribeToMarketData();
    }

    template<typename T>
    StrategyServer<T>::~StrategyServer()
    {
        logger.logInfo(CLASS, "DTOR", "Destroying StrategyServer");

        marketDataClient.stop();
        for (const auto& queueProcessor : queueProcessors)
        {
            queueProcessor->stop();
            delete queueProcessor;
        }

        for (const auto& strategyEngine : strategyEngines)
        {
            delete strategyEngine;
        }
    }

    // Creates the engines and listener. The number of threads is configurable to partition the
    // system by symbol ranges (improves latency and throughput). Each thread can be also
    // configured to have multiple listeners. The typical use case is to have one engine thread
    // to ensure sequencing of each engine. Any additional listener should only be used for logging.
    template<typename T>
    void StrategyServer<T>::createThreads()
    {
        for (uint32_t thread = 0; thread < numEngineThreads; ++thread)
        {
            // When numListeners > numEngineThreads, the extra threads should be used for logging
            for (uint32_t listenerId = 0; listenerId < (numListeners / numEngineThreads); ++listenerId)
            {
                strategyEngines.emplace_back(new StrategyEngine<T>{*this, thread});
            }

            // Each engine gets its own CLFQ
            queueProcessors.emplace_back(new CLFQProcessor{});
        }
    }

    // Calculates the positive modulo from the instrumentId and numEngineThreads.
    // Returns the engine at the associated index
    template<typename T>
    uint32_t StrategyServer<T>::getEngineThread(const uint32_t& instrumentId) const
    {
        return ((instrumentId % numEngineThreads) + numEngineThreads) % numEngineThreads;
    }

    // Schedules entities for processing by enqueueing them into a concurrent queue
    template<typename T>
    void StrategyServer<T>::scheduleJob(const uint32_t& instrumentId,
                                        const MarketData::Quote& quote,
                                        const Common::Bbo& bbo)
    {
        queueProcessors.at(getEngineThread(instrumentId))->enqueue([&]() {
            strategyEngines.at(getEngineThread(instrumentId))->onOrderBookUpdate(quote, bbo);
        });
    }

    // Creates a callback for the streaming processor to schedule book updates onto the engine
    template<typename T>
    void StrategyServer<T>::subscribeToMarketData()
    {
        callback = [&](const uint32_t& instrumentId,
                       const MarketData::Quote& quote,
                       const Common::Bbo& bbo) -> void {
            try
            {
                scheduleJob(instrumentId, quote, bbo);
            }
            catch (const std::exception& e)
            {
                logger.logSevere(CLASS, "subscribeToMarketData", e.what());
            }
        };

        marketDataClient.subscribe(marketDataClient, callback);
    }

} // namespace BeaconTech::Strategies


#endif