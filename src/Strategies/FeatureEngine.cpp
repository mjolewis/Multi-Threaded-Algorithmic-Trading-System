//
// A minimal feature engine whose protocol is to compute features that the algos will use to
// drive their trading strategy.
//
// Current features include:
// 1) Fair market value, which is derived from price and quantity updates in the order book.
//
// Created by Michael Lewis on 10/24/23.
//

#include "FeatureEngine.hpp"
#include "MessageObjects/MarketData/Quote.hpp"
#include "CommonServer/TypeSystem/NumericTypes.hpp"

namespace BeaconTech::Strategies
{
    FeatureEngine::FeatureEngine() : marketPrice{Common::NaN}
    {

    }

    double FeatureEngine::getMarketPrice() const
    {
        return marketPrice;
    }

    // Calculates the fair market price.
    // It is the weighted price of the current BBO and moves to where the market is trending.
    // For example, the market is likely to trend toward the offer when there are more open bids,
    // so the fair price is tilted toward the offer. Conversely, the market is likely to trend toward
    // the bid when there are more open offers, so the fair price is tilted toward the bid.
    void FeatureEngine::onOrderBookUpdate(const MessageObjects::Quote& quote, const Common::Bbo& bbo)
    {
        std::uint32_t instrumentId;
        MessageObjects::PriceLevel bestBid{};
        MessageObjects::PriceLevel bestAsk{};
        std::tie(instrumentId, bestBid, bestAsk) = bbo;

        double bidPrice = bestBid.price;
        double bidSize = static_cast<double>(bestBid.size);
        double askPrice = bestAsk.price;
        double askSize = static_cast<double>(bestAsk.size);

        marketPrice = (bidPrice * askSize + askPrice * bidSize) / (bidSize + askSize);
    }
} // BeaconTech