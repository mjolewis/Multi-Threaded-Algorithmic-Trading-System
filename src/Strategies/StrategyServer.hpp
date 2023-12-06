//
// The main entry point for all downstream business logic. The server is responsible
// for creating engines and facilitating the handoff between inbound data and the
// deterministic message processing queue that feeds the engines
//
// Created by Michael Lewis on 10/4/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYSERVER_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYSERVER_HPP

#include <iostream>
#include <vector>
#include <future>
#include <functional>
#include <memory>

#include "StrategyEngine.hpp"
#include "MarketData/clients/MarketDataHistoricalClient.hpp"
#include "MarketData/clients/MarketDataLiveClient.hpp"
#include "MessageObjects/marketdata/Quote.hpp"
#include "CommonServer/types/MdTypes.hpp"
#include "CommonServer/datastructures/ConcurrentQueueProcessor.hpp"
#include "CommonServer/datastructures/ConcurrentLockFreeQueue.hpp"
#include "StrategyCommon/handlers/CLFQProcessor.hpp"
#include "MessageObjects/marketdata/Quote.hpp"

namespace BeaconTech::Strategies
{
    // Forward Declarations
    template<typename T>
    class StrategyEngine;

    using CLFQProcessor = Common::CLFQProcessor<std::function<void ()>>;

    template<typename T>
    class StrategyServer
    {
    private:
        uint32_t numEngineThreads;
        uint32_t numListeners;
        std::vector<std::unique_ptr<StrategyEngine<T>>> strategyEngines;
        std::vector<std::unique_ptr<CLFQProcessor>> queueProcessors;
        T marketDataClient;
        Common::MdCallback callback;

    public:
        StrategyServer();

        virtual ~StrategyServer();

        void createThreads();

        uint32_t getEngineThread(const uint32_t& instrumentId) const;

        void subscribeToMarketData();

        void scheduleJob(const std::uint32_t& instrumentId, const MarketData::Quote& quote, const Common::Bbo& bbo);

        // Deleted default ctors and assignment operators
        StrategyServer(const StrategyServer<T>& other) = delete;

        StrategyServer(StrategyServer<T>&& other) = delete;

        StrategyServer<T>& operator=(const StrategyServer<T>& other) = delete;

        StrategyServer<T>& operator=(StrategyServer<T>&& other) = delete;
    };

} // namespace BeaconTech::Strategies


// ********** Template Definitions **********
#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYSERVER_CPP
#include "StrategyServer.cpp"
#endif //#MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYSERVER_CPP

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYSERVER_HPP
