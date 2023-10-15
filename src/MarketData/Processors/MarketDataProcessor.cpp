//
// Processes binary encoded market data from the provider and transforms it into a common format
// for consumption by  downstream components
//
// Created by Michael Lewis on 10/2/23.
//

#include <databento/timeseries.hpp>

#include "MarketDataProcessor.hpp"
#include "MarketData/MarketDataUtils.hpp"
#include "CommonServer/Utils/BTConcepts.hpp"

namespace BeaconTech::MarketData
{

    MarketDataProcessor::MarketDataProcessor() : orderBook{}
    {

    }

    MarketDataProcessor& MarketDataProcessor::operator=(const MarketDataProcessor& other)
    {
        // Avoid self-assignment
        if (this == &other) return *this;

        orderBook = other.orderBook;
        callback  = other.callback;

        return *this;
    }

    MarketDataProcessor& MarketDataProcessor::operator=(MarketDataProcessor&& other) noexcept
    {
        // Avoid self-assigment
        if (this == &other) return *this;

        orderBook = other.orderBook;
        callback = std::move(other.callback);

        return *this;
    }

    void MarketDataProcessor::initialize(const MdCallback& _callback)
    {
        this->callback = _callback;
    }

    // Handles incoming quotes and applies it to the order book.
    // The quotes are MBOs (Market by Order); however, this is configurable.
    // Performs compile-time validation via a Concept
    template<typename T>
    requires Mbbo<T>
    void MarketDataProcessor::handle(const T& mbbo)
    {
        orderBook.apply(mbbo);
        callback(mbbo.hd.instrument_id, orderBook.getBbos());
        MarketDataUtils::printBbos(mbbo, orderBook.getBbos());
    }

    // The system is currently designed for high-frequency trading. As a result, it only cares about quotes.
    // A decision should be made regarding whether we want to participate in lower frequency volume based
    // trading. If so, trades will be required for algos such as VWAP.
    // Performs compile-time validation via a Concept
    template<typename T>
    requires Trade<T>
    void MarketDataProcessor::handle(const T& trade)
    {
        /*
        auto instrumentId = trade.hd.instrument_id;
        auto timestamp = trade.hd.ts_event;
        auto action = trade.action;
        auto price = trade.price;
        auto depth = trade.depth;
        auto side = trade.side;
        auto size = trade.size;
        */
    }

    // Process the book update from the Consumer. OrderBook updates are subsequently delegated to
    // a templated handler that performs compile-time validation via Concepts
    databento::KeepGoing MarketDataProcessor::processBookUpdate(const databento::Record& record)
    {
        auto mbo = record.Get<databento::MboMsg>();
        handle<databento::MboMsg>(mbo);

        auto trade = record.Get<databento::TradeMsg>();
        handle<databento::TradeMsg>(trade);

        return databento::KeepGoing::Continue;
    }
} // namespace BeaconTech::MarketData