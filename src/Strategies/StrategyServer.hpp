//
// Created by Michael Lewis on 10/4/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYSERVER_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYSERVER_HPP

#include <vector>
#include <future>

#include "StrategyEngine.hpp"
#include "MarketData/Clients/MarketDataHistoricalClient.hpp"
#include "MarketData/Clients/MarketDataLiveClient.hpp"

namespace BeaconTech::Strategies
{

    // Forward Declarations
    template<typename T>
    class StrategyEngine;

    template<typename T>
    class StrategyServer
    {
    private:
        std::vector<StrategyEngine<T>> strategyEngines;
        T marketDataClient;
        int numThreads;
//        std::vector<std::async> threadPool;

    public:
        StrategyServer();
        virtual ~StrategyServer() = default;

        void createThreads();
    };

} // namespace BeaconTech::Strategies


// ********** Template Definitions **********
#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYSERVER_CPP
#include "StrategyServer.cpp"
#endif //#MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYSERVER_CPP

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYSERVER_HPP
