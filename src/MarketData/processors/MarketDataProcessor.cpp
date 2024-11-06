//
// Processes binary encoded market data from the provider and transforms it into a common format
// for consumption by  downstream components
//
// Created by Michael Lewis on 10/2/23.
//

#include <tuple>

#include <databento/timeseries.hpp>

#include "MarketDataProcessor.hpp"
#include "../../MarketData/MarketDataUtils.hpp"
#include "../../MessageObjects/marketdata/Quote.hpp"

namespace BeaconTech::MarketData
{

    MarketDataProcessor::MarketDataProcessor() : orderBook{}
    {

    }

    void MarketDataProcessor::initialize(const Common::MdCallback& _callback)
    {
        this->callback = _callback;
    }

    // Handles incoming market by order messages and updates the order book.
    // Performs compile-time validation via a Concept
    template<typename T>
    requires Common::Mbbo<T>
    void MarketDataProcessor::handle(const T& mbbo)
    {
        const MarketData::Quote* quote = orderBook.apply(mbbo);

        // FlagSet::kLast indicates the last message in the packet from the venue for a given instrument
        // and the book should only be inspected for the instrument after this messages is received
        if (mbbo.flags.kLast <= 0) return;

        if (quote == nullptr) [[unlikely]] return;

        std::uint32_t instrumentId = mbbo.hd.instrument_id;
        const Common::Bbo* bbo = orderBook.getBbo(instrumentId);

        // Only send downstream when bbo is valid
        if (bbo == nullptr) [[unlikely]] return;

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

        // todo uncomment if we want to build liquidity taking strategies
        // auto trade = record.Get<databento::TradeMsg>();
        // handle<databento::TradeMsg>(trade);

        return databento::KeepGoing::Continue;
    }
} // namespace BeaconTech::marketdata