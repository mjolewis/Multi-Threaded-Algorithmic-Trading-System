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

#include <unordered_map>
#include <tuple>
#include <utility>

#include <databento/timeseries.hpp>
#include "databento/fixed_price.hpp"

#include "Book.hpp"
#include "PriceLevel.hpp"
#include "Side.hpp"
#include "OrderAction.hpp"
#include "Quote.hpp"

namespace BeaconTech::MessageObjects
{
    Book::Book() : quotes{std::make_shared<std::unordered_map<std::uint64_t, Quote>>()}
    {

    }

    std::tuple<PriceLevel, PriceLevel> Book::getBbo()
    {
        auto bestAsk = PriceLevel();
        auto bestBid = PriceLevel();

        for (auto& it : *quotes)
        {
            const auto quote = it.second;
            if (quote.side == Side::SELL)
            {
                if (bestAsk.price == 0 || bestAsk.price > quote.price)
                {
                    bestAsk.price = quote.price;
                    bestAsk.size = quote.size;
                    bestAsk.count = 1;
                }
                else if (bestAsk.price == quote.price)
                {
                    bestAsk.size += quote.size;
                    ++bestAsk.count;
                }
            }
            else if (quote.side == Side::BUY)
            {
                if (bestBid.price < quote.price)
                {
                    bestBid.price = quote.price;
                    bestBid.size = quote.size;
                    bestBid.count = 1;
                }
                else if (bestBid.price == quote.price)
                {
                    bestBid.size += quote.size;
                    ++bestBid.count;
                }
            }
        }

        return {bestBid, bestAsk};
    }

    void Book::apply(const databento::MboMsg& mboMsg)
    {
        auto timestamp = mboMsg.hd.ts_event;
        auto action = mboMsg.action;
        auto side = (char) mboMsg.side;
        auto orderId = mboMsg.order_id;
        auto price = float(mboMsg.price) / float(databento::kFixedPriceScale);
        auto size = mboMsg.size;

        // Trade or Fill -> No change to book because all fills are
        // accompanied by cancel actions that do update the book
        if (action == OrderAction::TRADE.getFixCode() || action == OrderAction::FILL.getFixCode())
        {
            return;
        }

        // Clear -> Clear all resting orders
        if (action == OrderAction::CLEAR.getFixCode())
        {
            quotes->clear();
            return;
        }

        // Add -> Add a new order
        if (action == OrderAction::ADD.getFixCode())
        {
            Side side_ = Side::fromFix(side);
            Quote quote_ = Quote{side_, price, size, timestamp};
            quotes->insert(std::make_pair(orderId, quote_));
            return;
        }

        // Cancel -> Partial or full cancel
        if (action == OrderAction::CANCEL.getFixCode())
        {
            auto restingOrder = quotes->find(orderId);
            if (restingOrder != quotes->cend() && restingOrder->second.size >= size)
            {
                restingOrder->second.size -= size;

                // Remove orders that are fully cancelled
                if (restingOrder->second.size == 0)
                {
                    quotes->erase(restingOrder);
                }
            }

            return;
        }

        // Modify -> Modifies the price or size
        if (action == OrderAction::MODIFY.getFixCode())
        {
            auto restingOrder = quotes->find(orderId);
            if (restingOrder != quotes->cend())
            {
                // Assume order loses priority if price changes or size increases
                if (restingOrder->second.price != price || restingOrder->second.size < size)
                {
                    restingOrder->second.timestamp = timestamp;
                }

                restingOrder->second.size = size;
                restingOrder->second.price = price;
            }

            return;
        }
    }

} // namespace BeaconTech::MessageObjects