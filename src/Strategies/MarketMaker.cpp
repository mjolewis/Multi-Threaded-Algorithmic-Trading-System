//
// A Market Making trading algorithm. Its protocol is to make a profit by capturing the spread.
// To facilitate this, the algorithm continuously sends both passive bids and asks into the market.
// Profit depends on being able to adjust price and size levels on open orders based on changing
// market conditions faster than competitors.
//
// Because the algorithm must continuously supply passive liquidity into the market, managing inventory
// is crucial. Whenever a trade occurs, the algorithm must quickly unwind the inventory to manage risk
// to avoid unfavorable market price dynamics between the buys and sells.
//
// Created by Michael Lewis on 10/22/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETMAKER_CPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETMAKER_CPP

#include <memory>

#include "MarketMaker.hpp"
#include "StrategyEngine.hpp"
#include "MessageObjects/MarketData/Quote.hpp"

namespace BeaconTech::Strategies
{
    template<typename T>
    MarketMaker<T>::MarketMaker(StrategyEngine<T>& engine) : engine{engine}
    {
        // Initialize callbacks for the engine
        engine.onOrderBookUpdateAlgo = [this](auto quote, auto bbos) -> void { onOrderBookUpdate(quote, bbos); };
    }

    // Process book update, calculate bid and offer prices, validate notional limits
    // and creates/modifies/cancels passive orders
    template<typename T>
    void MarketMaker<T>::onOrderBookUpdate(const MessageObjects::Quote& quote, const std::shared_ptr<Common::Bbos>& bbos)
    {
        std::cout << "onOrderBookUpdate Callback" << std::endl;
    }
} // BeaconTech

#endif