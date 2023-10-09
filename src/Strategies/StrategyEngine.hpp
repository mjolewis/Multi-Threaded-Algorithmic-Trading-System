//
// Created by Michael Lewis on 10/4/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYENGINE_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYENGINE_HPP

#include <memory>

#include "StrategyServer.hpp"
#include "MarketData/Clients/MarketDataHistoricalClient.hpp"
#include "MarketData/Clients/MarketDataLiveClient.hpp"

namespace BeaconTech::Strategies
{
    // Forward Declarations
    template<typename T>
    class StrategyServer;

    template<typename T>
    class StrategyEngine
    {
    private:
        std::shared_ptr<StrategyServer<T>> server;
        int threadId;

    public:
        StrategyEngine(const StrategyServer<T>& server, int threadId);
        virtual ~StrategyEngine() = default;
    };

} // namespace BeaconTech::Strategies

// ********** Template Definitions **********
#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYENGINE_CPP
#include "StrategyEngine.cpp"
#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYENGINE_CPP

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYENGINE_HPP
