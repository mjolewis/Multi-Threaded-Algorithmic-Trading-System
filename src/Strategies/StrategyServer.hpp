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
#include "MarketData/Clients/MarketDataHistoricalClient.hpp"
#include "MarketData/Clients/MarketDataLiveClient.hpp"
#include "MessageObjects/MarketData/Quote.hpp"
#include "CommonServer/TypeSystem/MdTypes.hpp"
#include "CommonServer/DataStructures/ConcurrentQueueProcessor.hpp"
#include "CommonServer/DataStructures/ConcurrentLockFreeQueue.hpp"
#include "StrategyCommon/Handlers/CLFQProcessor.hpp"
#include "MessageObjects/MarketData/Quote.hpp"

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
        int numEngineThreads;
        int numListeners;
        std::vector<std::shared_ptr<StrategyEngine<T>>> strategyEngines;
        std::vector<std::shared_ptr<CLFQProcessor>> queueProcessors;
        std::shared_ptr<T> marketDataClient;
        Common::MdCallback callback;

    public:
        StrategyServer();

        virtual ~StrategyServer();

        void createThreads();

        int getEngineThread(const int& instrumentId) const;

        void subscribeToMarketData();

        void scheduleJob(const std::uint32_t& instrumentId, const MessageObjects::Quote& quote, const Common::Bbo& bbo);

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
