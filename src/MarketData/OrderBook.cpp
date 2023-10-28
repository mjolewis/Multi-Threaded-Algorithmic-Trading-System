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

#include <unordered_map>
#include <utility>

#include "databento/timeseries.hpp"
#include "databento/fixed_price.hpp"

#include "OrderBook.hpp"
#include "MessageObjects/marketdata/PriceLevel.hpp"
#include "MessageObjects/marketdata/Side.hpp"
#include "MessageObjects/marketdata/OrderAction.hpp"
#include "MessageObjects/marketdata/Quote.hpp"
#include "CommonServer/typesystem/NumericTypes.hpp"

namespace BeaconTech::MarketData
{
    OrderBook::OrderBook() : orderBooks{std::make_shared<Common::OrderBooks>()},
        bbos{std::make_shared<Common::Bbos>()}, bbo{}
    {

    }

    const Quote* OrderBook::apply(const databento::MboMsg& mboMsg)
    {
        auto action = mboMsg.action;

        // Trade or Fill -> No change to book because all fills are
        // accompanied by cancel actions that do update the book
        if (action == OrderAction::TRADE.getFixCode() || action == OrderAction::FILL.getFixCode())
        {
            return nullptr;
        }

        auto instrumentId = mboMsg.hd.instrument_id;
        auto timestamp = mboMsg.hd.ts_event;
        auto side = (char) mboMsg.side;
        auto orderId = mboMsg.order_id;
        auto price = double(mboMsg.price) / databento::kFixedPriceScale;
        auto size = mboMsg.size;

        if (action == OrderAction::CLEAR.getFixCode())  // Clears all resting orders for the given instrumentId
        {
            const auto& orderBook = orderBooks->find(instrumentId);
            if (orderBook != orderBooks->cend())
            {
                orderBook->second.clear();
            }
        }
        else if (action == OrderAction::ADD.getFixCode())  // Adds a new order for the given instrumentId
        {
            const auto& orderBook = orderBooks->find(instrumentId);
            Side side_ = Side::fromFix(side);
            Quote quote = Quote{instrumentId, side_, price, size, timestamp};
            if (orderBook == orderBooks->cend())
            {
                orderBooks->insert({instrumentId, {{orderId, quote}}});
            }
            else
            {
                orderBook->second.insert(std::make_pair(orderId, quote));
            }

            return &(orderBooks->find(instrumentId)->second.find(orderId)->second);
        }
        else if (action == OrderAction::CANCEL.getFixCode())  // Partial or full cancel
        {
            const auto& orderBook = orderBooks->find(instrumentId);
            if (orderBook != orderBooks->cend())
            {
                auto restingOrder = orderBook->second.find(orderId);
                if (restingOrder != orderBook->second.cend() && restingOrder->second.size >= size)
                {
                    restingOrder->second.size -= size;

                    // Remove orders that are fully cancelled
                    if (restingOrder->second.size == 0)
                    {
                        orderBook->second.erase(restingOrder);
                    }
                }

                return &restingOrder->second;
            }
        }
        else if (action == OrderAction::MODIFY.getFixCode())  // Modifies the price or size
        {
            const auto& orderBook = orderBooks->find(instrumentId);
            if (orderBook != orderBooks->cend())
            {
                auto restingOrder = orderBook->second.find(orderId);
                if (restingOrder != orderBook->second.cend())
                {
                    // Order loses priority if price changes or size increases
                    if (restingOrder->second.price != price || restingOrder->second.size < size)
                    {
                        restingOrder->second.timestamp = timestamp;
                    }

                    restingOrder->second.size = size;
                    restingOrder->second.price = price;
                }

                return &restingOrder->second;
            }
        }

        return nullptr;
    }

    const Common::Bbo* OrderBook::getBbo(const std::uint32_t& instrumentId)
    {
        auto bestAsk = PriceLevel();
        auto bestBid = PriceLevel();

        const auto orderBookEntries = orderBooks->find(instrumentId);
        if (orderBookEntries != orderBooks->cend())
        {
            const auto orderBookEntry = orderBookEntries->second;
            for (const auto& order : orderBookEntry)
            {
                const auto& quote = order.second;
                if (quote.side == Side::SELL)
                {
                    if (isnan(bestAsk.price) || bestAsk.price > quote.price)
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
                    if (isnan(bestBid.price) || bestBid.price < quote.price)
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

                bbo = std::make_tuple(instrumentId, bestBid, bestAsk);
                if (bbos->find(instrumentId) != bbos->cend()) [[likely]] bbos->at(instrumentId) = bbo;
                else bbos->emplace(instrumentId, bbo);
            }

            return &bbo;
        }

        return nullptr;
    }

} // namespace BeaconTech::MessageObjects