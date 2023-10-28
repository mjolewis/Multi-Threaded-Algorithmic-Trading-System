//
// Created by Michael Lewis on 9/29/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_IMARKETDATAPROVIDER_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_IMARKETDATAPROVIDER_HPP

#include <functional>
#include <memory>

#include "MarketData/processors/MarketDataProcessor.hpp"

namespace BeaconTech::MarketData
{

    class IMarketDataProvider
    {
    public:
        IMarketDataProvider() = default;

        virtual ~IMarketDataProvider() = default;

        virtual std::function<void ()> getBookUpdate(std::shared_ptr<MarketDataProcessor>& streamingProcessor) = 0;

        virtual void stop() = 0;
    };
} // namespace BeaconTech::marketdata


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_IMARKETDATAPROVIDER_HPP
