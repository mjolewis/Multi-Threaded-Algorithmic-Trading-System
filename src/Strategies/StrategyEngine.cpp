//
// A high-performance and lock free engine model with deterministic message processing.
//
// Created by Michael Lewis on 10/4/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYENGINE_CPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYENGINE_CPP

#include <memory>

#include "StrategyEngine.hpp"
#include "StrategyServer.hpp"
#include "algos/MarketMaker.hpp"

namespace BeaconTech::Strategies
{
    template<typename T>
    StrategyEngine<T>::StrategyEngine(const StrategyServer<T>& server, uint32_t threadId)
        : server{server}, logger{CLASS_PATH, APP_NAME, threadId}, threadId{threadId},
          clock{std::make_shared<Common::Clock>()}, featureEngine{logger}
    {
        logger.logInfo(CLASS, "CTOR", "Creating StrategyEngine");

        marketMaker = new MarketMaker<T>{logger, clock, *this, featureEngine};
    }

    template<typename T>
    StrategyEngine<T>::~StrategyEngine()
    {
        logger.logInfo(CLASS, "DTOR", "Destroying StrategyEngine");
        delete this->marketMaker;
    }

    // Informs the feature engine and strategy about quotes and book updates
    template<typename T>
    void StrategyEngine<T>::onOrderBookUpdate(const MarketData::Quote& quote, const Common::Bbo& bbo)
    {
        featureEngine.onOrderBookUpdate(quote, bbo);
        onOrderBookUpdateAlgo(quote, bbo);
    }

} // namespace BeaconTech::Strategies


#endif