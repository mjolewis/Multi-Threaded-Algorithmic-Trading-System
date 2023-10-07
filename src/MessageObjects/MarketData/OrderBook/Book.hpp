//
// Tracks orders and updates them in the book according to different MGO actions.
// It keeps track of all resting orders, but not the book levels. Tracking book levels
// requires inefficiently iterating over all the orders to build levels. As a result,
// the system uses a more efficient order tracking approach.
//
// Note - This book is capable of tracking multiple instruments. This is achieved by
// building a Book of Books.
//
// Created by Michael Lewis on 10/6/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_BOOK_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_BOOK_HPP

#include <chrono>
#include <memory>
#include <unordered_map>
#include <string>

#include <databento/timeseries.hpp>

#include "Quote.hpp"
#include "PriceLevel.hpp"
#include "CommonServer/Utils/DataTime.hpp"

namespace BeaconTech::MessageObjects
{

    class Book
    {
    private:
        std::shared_ptr<std::unordered_map<std::uint64_t, Quote>> quotes;

    public:
        Book();
        virtual ~Book() = default;

        std::tuple<PriceLevel, PriceLevel> getBbo();

        void apply(const databento::MboMsg& mboMsg);
    };

} // namespace BeaconTech::MessageObjects

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_BOOK_HPP
