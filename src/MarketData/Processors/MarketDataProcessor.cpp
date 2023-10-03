//
// Created by Michael Lewis on 10/2/23.
//

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

    // todo - use concepts to enforce constraints on quotes
    databento::KeepGoing MarketDataProcessor::processQuote(const databento::Record& record)
    {
        auto mboMsg = record.Get<databento::MboMsg>();
        auto size = mboMsg.size;
        auto price = float(mboMsg.price) / float(databento::kFixedPriceScale);
        auto side = mboMsg.side;
        std::cout << mboMsg.hd.instrument_id << '\t' << size << '\t' << price << '\t' << side << '\n';
        return databento::KeepGoing::Continue;
    }
}