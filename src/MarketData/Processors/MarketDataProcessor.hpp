//
// Processes binary encoded market data from the provider and transforms it into a common format
// for consumption by  downstream components
//
// Created by Michael Lewis on 10/2/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAPROCESSOR_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAPROCESSOR_HPP

#include <databento/timeseries.hpp>

#include "MessageObjects/MarketData/OrderBook/Book.hpp"
#include "CommonServer/Utils/BTConcepts.hpp"
#include "CommonServer/Utils/MdTypes.hpp"

namespace BeaconTech::MarketData
{
    class MarketDataProcessor
    {
    private:
        MessageObjects::Book orderBook;
        MdCallback callback;

    public:
        MarketDataProcessor();
        virtual ~MarketDataProcessor() = default;

        // Operator Overloads
        MarketDataProcessor& operator=(const MarketDataProcessor& other);

        MarketDataProcessor& operator=(MarketDataProcessor&& other) noexcept;

        void initialize(const MdCallback& callback);

        // Book Updates
        template<typename T>
        requires Mbbo<T>
        void handle(const T& quote);

        template<typename T>
        requires Trade<T>
        void handle(const T& trade);

        databento::KeepGoing processBookUpdate(const databento::Record& record);
    };
} // namespace BeaconTech::MarketData


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAPROCESSOR_HPP
