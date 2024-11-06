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
#include <tuple>

#include "MarketMaker.hpp"
#include "../StrategyEngine.hpp"
#include "FeatureEngine.hpp"
#include "../../StrategyCommon/managers/OrderManager.hpp"
#include "../../CommonServer/utils/ConfigManager.hpp"
#include "../../MessageObjects/marketdata/Quote.hpp"
#include "../../MarketData/MarketDataUtils.hpp"
#include "../../CommonServer/utils/Clock.hpp"

namespace BeaconTech::Strategies
{
    template<typename T>
    MarketMaker<T>::MarketMaker(const BeaconTech::Common::Logger& logger, const std::shared_ptr<Common::Clock>& clock,
                                StrategyEngine<T>& strategyEngine, const FeatureEngine& featureEngine,
                                OrderManager& orderManager)
        : logger{logger}, clock{clock}, strategyEngine{strategyEngine}, featureEngine{featureEngine}, orderManager{orderManager},
          targetSpreadBps{Common::ConfigManager::doubleConfigValueDefaultIfNull("targetSpreadBps", 0.0002)},
          targetSize{Common::ConfigManager::intConfigValueDefaultIfNull("targetSize", 100)}
    {
        logger.logInfo(CLASS, "CTOR", "Creating MarketMaker");
        initializeCallbacks();
    }

    template<typename T>
    MarketMaker<T>::~MarketMaker()
    {
        logger.logInfo(CLASS, "DTOR", "Destroying MarketMaker");
    }

    template<typename T>
    void MarketMaker<T>::initializeCallbacks()
    {
        strategyEngine.onOrderBookUpdateAlgo = [this](auto quote, auto bbo) -> void { onOrderBookUpdate(quote, bbo); };
    }

    // Process the BBO, calculate fair market price, perform risk checks and create, modify, or cancel passive orders
    template<typename T>
    void MarketMaker<T>::onOrderBookUpdate(const MarketData::Quote& quote, const Common::Bbo& bbo)
    {
        double fairMarketPrice = featureEngine.getMarketPrice();
        if (std::isnan(fairMarketPrice)) return;

        MarketData::MarketDataUtils::printBbo(bbo, fairMarketPrice);

        double bidPrice = std::get<1>(bbo).price;
        double askPrice = std::get<2>(bbo).price;

        // Calculate bid and ask prices that the strategy will use for the passive orders it sends into
        // the market. A future release will upgrade the intelligence of this logic to dynamically determine
        // a based on the instrument because spreads vary across instruments. However, for now, the system
        // threshold uses a default config to set the target spread at 2% which is roughly the average
        // spread on NSDQ listed securities.
        //
        // The system will use the BBO on orders it sends into the market whenever the difference
        // between our fair market price and the BBO is >= to the threshold. The intuition is simple -
        // Use the BBO is when the security is undervalued (for bids) or overvalued (for asks)
        // relative to our fair market price.
        //
        // The system will use a $1 offset to the BBO for orders it sends into the market whenever
        // the difference between our fair market price and the BBO is less than the threshold.
        // The intuition is simple - Use the offset price when the security is overvalued (for bids)
        // and undervalue (for asks) relative to our fair market price. This offset logic helps
        // us to avoid being caught on the wrong side of the trade as the spread between our fair
        // price and the market is too narrow.
        bidPrice = bidPrice - (fairMarketPrice - bidPrice >= (bidPrice * targetSpreadBps) ? 0 : 1);
        askPrice = askPrice + (askPrice - fairMarketPrice >= (askPrice * targetSpreadBps) ? 0 : 1);

        orderManager.onOrderRequest(std::get<0>(bbo), bidPrice, askPrice, targetSize);
    }
} // BeaconTech

#endif