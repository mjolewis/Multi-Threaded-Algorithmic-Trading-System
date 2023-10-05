//
// Created by Michael Lewis on 10/2/23.
//

#include <concepts>
#include <iostream>

#include "databento/fixed_price.hpp"
#include <databento/timeseries.hpp>

#include "MarketDataProcessor.hpp"

namespace MarketData
{
    void MarketDataProcessor::initialize()
    {
        // silent for now
    }

    // The current system processes MBOs (Market by Order); however, this is configurable.
    // Compile-time validations enforced via a Concept.
    template<typename T>
    requires Quote<T>
    void MarketDataProcessor::handle(const T& quote)
    {
        auto instrumentId = quote.hd.instrument_id;
        auto timestamp = quote.hd.ts_event;
        auto action = quote.action;
        auto side = quote.side;
        auto orderId = quote.order_id;
        auto price = float(quote.price) / float(databento::kFixedPriceScale);
        auto size = quote.size;
        std::cout << instrumentId << '\t' << timestamp.time_since_epoch().count() << '\t' << action
                  << '\t' << side << '\t' << orderId << price  << size << '\t' << '\n';
    }

    // Compile-time validations enforced via a Concept.
    template<typename T>
    requires Trade<T>
    void MarketDataProcessor::handle(const T& trade)
    {
        auto instrumentId = trade.hd.instrument_id;
        auto timestamp = trade.hd.ts_event;
        auto action = trade.action;
        auto price = trade.price;
        auto depth = trade.depth;
        auto side = trade.side;
        auto size = trade.size;
        std::cout << instrumentId << '\t' << timestamp.time_since_epoch().count() << '\t' << action
                  << '\t' << price << '\t' << depth << side  << size << '\t' << '\n';
    }

    // Process the book update from the Consumer. Book updates are subsequently delegated to
    // a templated handler that performs compile-time validation via Concepts
    databento::KeepGoing MarketDataProcessor::processBookUpdate(const databento::Record& record)
    {
        auto mbo = record.Get<databento::MboMsg>();
        handle<databento::MboMsg>(mbo);

        auto trade = record.Get<databento::TradeMsg>();
        handle<databento::TradeMsg>(trade);

        return databento::KeepGoing::Continue;
    }
}