//
// A minimal feature engine whose protocol is to compute features that the algos will use to
// drive their trading strategy.
//
// Current features include:
// 1) Fair market value, which is derived from price and quantity updates in the order book.
//
// Created by Michael Lewis on 10/24/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_FEATUREENGINE_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_FEATUREENGINE_HPP

#include "../../CommonServer/logging/Logger.hpp"
#include "../../MarketData/OrderBook.hpp"

namespace BeaconTech::Strategies
{

    class FeatureEngine
    {
    private:
        inline static const std::string CLASS = "FeatureEngine";

        // Management properties
        const BeaconTech::Common::Logger& logger;

        // Feature properties
        double marketPrice;

    public:
        explicit FeatureEngine(const BeaconTech::Common::Logger& logger);

        virtual ~FeatureEngine();

        double getMarketPrice() const;

        void onOrderBookUpdate(const MarketData::Quote& quote, const Common::Bbo& bbo);

        // Deleted default ctors and assignment operators
        FeatureEngine(const FeatureEngine& other) = delete;

        FeatureEngine(FeatureEngine&& other) = delete;

        FeatureEngine& operator=(const FeatureEngine& other) = delete;

        FeatureEngine& operator=(FeatureEngine&& other) = delete;
    };

} // BeaconTech::Strategies

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_FEATUREENGINE_HPP
