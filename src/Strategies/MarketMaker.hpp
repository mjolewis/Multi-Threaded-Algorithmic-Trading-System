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

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETMAKER_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETMAKER_HPP

#include <functional>
#include <memory>

#include "StrategyEngine.hpp"
#include "MessageObjects/MarketData/Quote.hpp"
#include "StrategyCommon/FeatureEngine.hpp"

namespace BeaconTech::Strategies
{

    // Forward Declarations
    template<typename T>
    class StrategyEngine;

    template<typename T>
    class MarketMaker
    {
    private:
        StrategyEngine<T>& strategyEngine;
        const FeatureEngine& featureEngine;

    public:
        MarketMaker(StrategyEngine<T>& strategyEngine, const FeatureEngine& featureEngine);

        virtual ~MarketMaker() = default;

        void onOrderBookUpdate(const MessageObjects::Quote &quote, const Common::Bbo& bbo);

        // Deleted default ctors and assignment operators
        MarketMaker() = delete;

        MarketMaker(const MarketMaker<T>& other) = delete;

        MarketMaker(MarketMaker<T>&& other) = delete;

        MarketMaker<T>& operator=(const MarketMaker<T>& other) = delete;

        MarketMaker<T>& operator=(MarketMaker<T>&& other) = delete;
    };

} // BeaconTech::Strategies


//********** Start Template Definitions **********
#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETMAKER_CPP
#include "MarketMaker.cpp"
#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETMAKER_CPP
//********** End Template Definitions **********

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETMAKER_HPP
