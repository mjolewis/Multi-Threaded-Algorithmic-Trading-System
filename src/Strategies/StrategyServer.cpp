//
// The main entry point for all downstream business logic. The server is responsible
// for creating engines and facilitating the handoff between inbound data and the
// deterministic message processing queue that feeds the engines
//
// Created by Michael Lewis on 10/4/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYSERVER_CPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYSERVER_CPP

#include <cstdlib>
#include <exception>
#include <memory>

#include <databento/exceptions.hpp>

#include "StrategyServer.hpp"
#include "CommonServer/utils/ConfigManager.hpp"
#include "CommonServer/handlers/CLFQProcessor.hpp"
#include "MessageObjects/marketdata/Quote.hpp"
#include "CommonServer/logging/Logger.hpp"

namespace BeaconTech::Strategies
{

    // Overloaded ctor
    template<typename T>
    StrategyServer<T>::StrategyServer()
        : logger{CLASS},
          numEngineThreads{Common::ConfigManager::intConfigValueDefaultIfNull("numEngineThreads", 1)},
          numListeners{Common::ConfigManager::intConfigValueDefaultIfNull("numListeners", 1)},
          marketDataClient{"StrategyServer", &logger}
    {
//        try
//        {
//            marketDataClient = new T{"StrategyServer", &LOGGER};
//        }
//        catch (const databento::HttpResponseError& e)
//        {
//            LOGGER.logSevere(CLASS, "StrategyServer", "Databento Exception during startup");
//            exit(EXIT_FAILURE);
//        }
//        catch (std::exception& e)
//        {
//            LOGGER.logSevere(CLASS, "StrategyServer", "Exception Starting Server! %", e.what());
//        }

        createThreads();
        subscribeToMarketData();
    }

    template<typename T>
    StrategyServer<T>::~StrategyServer()
    {
        marketDataClient.stop();
        for (const auto& queueProcessor : queueProcessors) queueProcessor->stop();
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
                strategyEngines.emplace_back(std::make_unique<StrategyEngine<T>>(*this, thread, &logger));
            }

            queueProcessors.emplace_back(std::make_unique<CLFQProcessor>());
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