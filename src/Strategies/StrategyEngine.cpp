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
#include "MessageObjects/marketdata/Quote.hpp"
#include "Strategies/algos/MarketMaker.hpp"

namespace BeaconTech::Strategies
{
    template<typename T>
    StrategyEngine<T>::StrategyEngine(const StrategyServer<T>& server, const unsigned int& threadId,
                                      BeaconTech::Common::Logger* logger)
        : server{server}, logger(logger), threadId{threadId}, clock{std::make_shared<Common::Clock>()},
          featureEngine{}, orderManager{std::make_shared<OrderManager>(clock)}
    {
        logger->logInfo(CLASS, "StrategyEngine", "Creating StrategyEngine");

        marketMaker = std::make_shared<MarketMaker<T>>(*this, clock, featureEngine, orderManager);
    }

    // Informs the feature engine and strategy about quotes and book updates
    template<typename T>
    void StrategyEngine<T>::onOrderBookUpdate(const MarketData::Quote& quote, const Common::Bbo& bbo)
    {
        logger->logInfo(CLASS, "onOrderBookUpdate", "Received BBO");

        featureEngine.onOrderBookUpdate(quote, bbo);
        onOrderBookUpdateAlgo(quote, bbo);
    }

} // namespace BeaconTech::Strategies


#endif