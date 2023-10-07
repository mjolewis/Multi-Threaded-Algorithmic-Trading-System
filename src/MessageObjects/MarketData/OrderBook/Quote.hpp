//
// Represents a resting order in the book.
//
// Created by Michael Lewis on 10/6/23.

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_QUOTE_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_QUOTE_HPP

#include <chrono>
#include <string>
#include <utility>

#include "Side.hpp"
#include "CommonServer/Utils/DataTime.hpp"

namespace BeaconTech::MessageObjects
{

    struct Quote
    {
        BeaconTech::MessageObjects::Side side;
        double price{};
        std::uint32_t size{};
        UnixNanos timestamp{};

        Quote(BeaconTech::MessageObjects::Side side, double price, std::uint32_t size, UnixNanos timestamp)
            : side{std::move(side)}, price{price}, size{size}, timestamp{timestamp}
        {

        }
    };
} // namespace BeaconTech::MessageObjects


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_QUOTE_HPP
