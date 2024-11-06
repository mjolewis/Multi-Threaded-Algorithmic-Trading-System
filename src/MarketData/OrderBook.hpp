//
// Tracks orders and updates them in the book according to different MGO actions.
// It keeps track of all resting orders, but not the book levels. Tracking book levels
// requires inefficiently iterating over all the orders to build levels. As a result,
// the system uses a more efficient order tracking approach.
//
// This book is capable of tracking multiple instruments. This is achieved using
// a composite data structure that maintains a separate book for each instrument.
//
// Created by Michael Lewis on 10/6/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERBOOK_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERBOOK_HPP

#include <chrono>
#include <memory>
#include <unordered_map>
#include <string>
#include <utility>

#include "databento/timeseries.hpp"

#include "../CommonServer/types/MdTypes.hpp"
#include "../MessageObjects/marketdata/Quote.hpp"
#include "../MessageObjects/marketdata/PriceLevel.hpp"
#include "../CommonServer/types/DateTimes.hpp"

namespace BeaconTech::MarketData
{
    class OrderBook
    {
    private:
        Common::OrderBooks* orderBooks; // instrumentId -> orderBook
        Common::Bbos* bbos; // instrumentId -> priceLevels
        Common::Bbo bbo; // priceLevels for the current book update

    public:
        OrderBook();

        virtual ~OrderBook();

        const Quote* apply(const databento::MboMsg& mboMsg);

        const Common::Bbo* getBbo(const std::uint32_t& instrumentId);
    };

} // namespace BeaconTech::MarketData


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERBOOK_HPP
