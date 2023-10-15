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

#include "cmake-build-debug/_deps/databento-src/include/databento/timeseries.hpp"

#include "CommonServer/Utils/MdTypes.hpp"
#include "src/MessageObjects/MarketData/Quote.hpp"
#include "src/MessageObjects/MarketData/PriceLevel.hpp"
#include "CommonServer/Utils/DateTimes.hpp"

namespace BeaconTech::MessageObjects
{
    class OrderBook
    {
    private:
        std::shared_ptr<OrderBooks> orderBooks; // instrumentId -> orderId -> orderBook
        std::shared_ptr<Bbos> bbos; // instrumentId -> priceLevels

    public:
        OrderBook();
        virtual ~OrderBook() = default;

        void apply(const databento::MboMsg& mboMsg);

        const std::shared_ptr<Bbos>& getBbos();
    };

} // namespace BeaconTech::MessageObjects


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERBOOK_HPP
