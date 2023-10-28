//
// Processes binary encoded market data from the provider and transforms it into a common format
// for consumption by  downstream components
//
// Created by Michael Lewis on 10/2/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAPROCESSOR_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAPROCESSOR_HPP

#include <databento/timeseries.hpp>

#include "MarketData/OrderBook.hpp"
#include "CommonServer/concepts/BTConcepts.hpp"
#include "CommonServer/typesystem/MdTypes.hpp"

namespace BeaconTech::MarketData
{
    class MarketDataProcessor
    {
    private:
        MessageObjects::OrderBook orderBook;
        Common::MdCallback callback;

    public:
        MarketDataProcessor();

        virtual ~MarketDataProcessor() = default;

        void initialize(const Common::MdCallback& callback);

        // OrderBook Updates
        template<typename T>
        requires Common::Mbbo<T>
        void handle(const T& quote);

        template<typename T>
        requires Common::Trade<T>
        void handle(const T& trade);

        databento::KeepGoing processBookUpdate(const databento::Record& record);

        // Deleted default ctors and assignment operators
        MarketDataProcessor(const MarketDataProcessor& other) = delete;

        MarketDataProcessor(MarketDataProcessor&& other) = delete;

        MarketDataProcessor& operator=(const MarketDataProcessor& other) = delete;

        MarketDataProcessor& operator=(MarketDataProcessor&& other) = delete;
    };
} // namespace BeaconTech::marketdata


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAPROCESSOR_HPP
