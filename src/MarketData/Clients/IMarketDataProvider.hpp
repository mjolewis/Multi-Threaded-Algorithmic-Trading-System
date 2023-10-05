//
// Created by Michael Lewis on 9/29/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_IMARKETDATAPROVIDER_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_IMARKETDATAPROVIDER_HPP

#include <functional>
#include <memory>

namespace MarketData
{
    class IMarketDataProvider
    {
    public:
        IMarketDataProvider() = default;
        virtual ~IMarketDataProvider() = default;

        virtual std::shared_ptr<IMarketDataProvider> getClient() const = 0;
        virtual std::function<void ()> getBookUpdate() const = 0;
    };
}

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_IMARKETDATAPROVIDER_HPP
