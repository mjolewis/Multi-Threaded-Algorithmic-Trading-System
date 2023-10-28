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
    StrategyEngine<T>::StrategyEngine(const StrategyServer<T>& server, const unsigned int& threadId)
        : server{server}, threadId{threadId}, featureEngine{}, orderManager{std::make_shared<OrderManager>()}
    {
        marketMaker = std::make_shared<MarketMaker<T>>(*this, featureEngine, orderManager);
    }

    // Informs the feature engine and strategy about quotes and book updates
    template<typename T>
    void StrategyEngine<T>::onOrderBookUpdate(const MessageObjects::Quote& quote, const Common::Bbo& bbo)
    {
        featureEngine.onOrderBookUpdate(quote, bbo);
        onOrderBookUpdateAlgo(quote, bbo);
    }

} // namespace BeaconTech::Strategies


#endif