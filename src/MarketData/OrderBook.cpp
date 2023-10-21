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

#include "cmake-build-debug/_deps/databento-src/include/databento/timeseries.hpp"
#include "databento/fixed_price.hpp"

#include "OrderBook.hpp"
#include "src/MessageObjects/MarketData/PriceLevel.hpp"
#include "src/MessageObjects/MarketData/Side.hpp"
#include "src/MessageObjects/MarketData/OrderAction.hpp"
#include "src/MessageObjects/MarketData/Quote.hpp"

namespace BeaconTech::MessageObjects
{
    OrderBook::OrderBook() : orderBooks{std::make_shared<Common::OrderBooks>()}, bbos{std::make_shared<Common::Bbos>()}
    {

    }

    void OrderBook::apply(const databento::MboMsg& mboMsg)
    {
        auto action = mboMsg.action;

        // Trade or Fill -> No change to book because all fills are
        // accompanied by cancel actions that do update the book
        if (action == OrderAction::TRADE.getFixCode() || action == OrderAction::FILL.getFixCode())
        {
            return;
        }

        auto instrumentId = mboMsg.hd.instrument_id;
        auto timestamp = mboMsg.hd.ts_event;
        auto side = (char) mboMsg.side;
        auto orderId = mboMsg.order_id;
        auto price = mboMsg.price;
        auto size = mboMsg.size;

        // Clear -> Clear all resting orders for the given instrumentId
        if (action == OrderAction::CLEAR.getFixCode())
        {
            const auto& orderBook = orderBooks->find(instrumentId);
            if (orderBook != orderBooks->cend())
            {
                orderBook->second.clear();
            }

            return;
        }

        // Add -> Add a new order for the given instrumentId
        if (action == OrderAction::ADD.getFixCode())
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
            return;
        }

        // Cancel -> Partial or full cancel
        if (action == OrderAction::CANCEL.getFixCode())
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
            }

            return;
        }

        // Modify -> Modifies the price or size
        if (action == OrderAction::MODIFY.getFixCode())
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
            }

            return;
        }
    }

    const std::shared_ptr<Common::Bbos>& OrderBook::getBbos()
    {
        auto bestAsk = PriceLevel();
        auto bestBid = PriceLevel();

        for (const auto& orderBook : *orderBooks)
        {
            const auto& orders = orderBook.second;
            for (const auto& orderId : orders)
            {
                const auto& order = orderId.second;
                if (order.side == Side::SELL)
                {
                    if (bestAsk.price == 0 || bestAsk.price > order.price)
                    {
                        bestAsk.price = order.price;
                        bestAsk.size = order.size;
                        bestAsk.count = 1;
                    }
                    else if (bestAsk.price == order.price)
                    {
                        bestAsk.size += order.size;
                        ++bestAsk.count;
                    }
                }
                else if (order.side == Side::BUY)
                {
                    if (bestBid.price < order.price)
                    {
                        bestBid.price = order.price;
                        bestBid.size = order.size;
                        bestBid.count = 1;
                    }
                    else if (bestBid.price == order.price)
                    {
                        bestBid.size += order.size;
                        ++bestBid.count;
                    }
                }
            }

            const auto instrumentId = orderBook.first;
            bbos->emplace(instrumentId, std::make_pair(bestBid, bestAsk));
        }

        return bbos;
    }

} // namespace BeaconTech::MessageObjects