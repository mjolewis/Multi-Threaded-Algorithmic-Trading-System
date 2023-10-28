//
// Processes binary encoded market data from the provider and transforms it into a common format
// for consumption by  downstream components
//
// Created by Michael Lewis on 10/2/23.
//

#include <tuple>

#include <databento/timeseries.hpp>

#include "MarketDataProcessor.hpp"
#include "MarketData/MarketDataUtils.hpp"
#include "CommonServer/concepts/BTConcepts.hpp"
#include "MessageObjects/marketdata/Quote.hpp"
#include "CommonServer/typesystem/NumericTypes.hpp"

namespace BeaconTech::MarketData
{

    MarketDataProcessor::MarketDataProcessor() : orderBook{}
    {

    }

    void MarketDataProcessor::initialize(const Common::MdCallback& _callback)
    {
        this->callback = _callback;
    }

    // Handles incoming quotes and applies it to the order book.
    // The quotes are MBOs (Market by Order); however, this is configurable.
    // Performs compile-time validation via a Concept
    template<typename T>
    requires Common::Mbbo<T>
    void MarketDataProcessor::handle(const T& mbbo)
    {
        const MarketData::Quote* quote = orderBook.apply(mbbo);
        if (quote == nullptr) return;

        std::uint32_t instrumentId = mbbo.hd.instrument_id;
        const Common::Bbo* bbo = orderBook.getBbo(instrumentId);

        // Only send downstream when bbo is valid
        if (bbo == nullptr) return;
        if (isnan(std::get<1>(*bbo).price) || isnan(std::get<2>(*bbo).price)) return;

        callback(instrumentId, *quote, *bbo);
    }

    // The system is currently focused on market making strategies. As a result, the system is only processing
    // mbo messages. However, the system is flexible enough to also use liquidity taking strategies. As a result,
    // we have a noop interface to consumes trades, which are important for liquidity taking strategies.
    // Performs compile-time validation via a Concept
    template<typename T>
    requires Common::Trade<T>
    void MarketDataProcessor::handle(const T& trade)
    {
        // noop
    }

    // Process the book update from the Consumer. OrderBook updates are subsequently delegated to
    // a templated handler that performs compile-time validation via concepts
    databento::KeepGoing MarketDataProcessor::processBookUpdate(const databento::Record& record)
    {
        auto mbo = record.Get<databento::MboMsg>();
        handle<databento::MboMsg>(mbo);

        auto trade = record.Get<databento::TradeMsg>();
        handle<databento::TradeMsg>(trade);

        return databento::KeepGoing::Continue;
    }
} // namespace BeaconTech::marketdata