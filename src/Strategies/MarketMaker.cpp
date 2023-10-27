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
#include "StrategyCommon/FeatureEngine.hpp"
#include "CommonServer/TypeSystem/NumericTypes.hpp"
#include "MarketData/MarketDataUtils.hpp"

namespace BeaconTech::Strategies
{
    template<typename T>
    MarketMaker<T>::MarketMaker(StrategyEngine<T>& strategyEngine, const FeatureEngine& featureEngine)
        : strategyEngine{strategyEngine}, featureEngine{featureEngine}
    {
        // Initialize callbacks for the strategyEngine
        strategyEngine.onOrderBookUpdateAlgo = [this](auto quote, auto bbo) -> void { onOrderBookUpdate(quote, bbo); };
    }

    // Process the BBO, calculate fair market price, perform risk checks and create, modify, or cancel passive orders
    template<typename T>
    void MarketMaker<T>::onOrderBookUpdate(const MessageObjects::Quote& quote, const Common::Bbo& bbo)
    {
        double fairMarketPrice = featureEngine.getMarketPrice();
        if (fairMarketPrice != Common::NaN)
        {
            MarketData::MarketDataUtils::printBbo(bbo, fairMarketPrice);
        }
    }
} // BeaconTech

#endif