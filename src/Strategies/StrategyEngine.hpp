//
// A high-performance and lock free engine model with deterministic message processing.
//
// Created by Michael Lewis on 10/4/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYENGINE_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYENGINE_HPP

#include <memory>
#include <string>

#include "StrategyServer.hpp"
#include "../MarketData/clients/MarketDataHistoricalClient.hpp"
#include "../MarketData/clients/MarketDataLiveClient.hpp"
#include "../MarketData/OrderBook.hpp"
#include "../MessageObjects/marketdata/Quote.hpp"
#include "algos/MarketMaker.hpp"
#include "algos/FeatureEngine.hpp"
#include "../StrategyCommon/managers/OrderManager.hpp"
#include "../CommonServer/utils/Clock.hpp"
#include "../CommonServer/logging/Logger.hpp"

namespace BeaconTech::Strategies
{
    // Forward Declarations
    template<typename T>
    class StrategyServer;

    template<typename T>
    class MarketMaker;

    template<typename T>
    class StrategyEngine
    {
    private:
        inline static const std::string CLASS_PATH = CLASS_FILE_PATH;
        inline static const std::string APP_NAME = "STRATEGIES";
        inline static const std::string CLASS = "StrategyEngine";

        const StrategyServer<T>& server;

        // Mgmt properties
        const BeaconTech::Common::Logger logger;
        uint32_t threadId;
        std::shared_ptr<Common::Clock> clock;

        // Strategy properties
        FeatureEngine featureEngine;
        OrderManager* orderManager;
        MarketMaker<T>* marketMaker;

    public:
        StrategyEngine(const StrategyServer<T>& server, const uint32_t threadId);

        virtual ~StrategyEngine();

        void onOrderBookUpdate(const MarketData::Quote& quote, const Common::Bbo& bbo);

        // Callbacks that dispatch order book updates and downstream responses to the trading algorithm
        std::function<void (const MarketData::Quote &quote, const Common::Bbo& bbo)> onOrderBookUpdateAlgo;

        // Deleted default ctors and assignment operators
        StrategyEngine() = delete;

        StrategyEngine(const StrategyEngine<T>& other) = delete;

        StrategyEngine(StrategyEngine<T>&& other) = delete;

        StrategyEngine<T> operator=(const StrategyEngine<T>& other) = delete;

        StrategyEngine<T> operator=(StrategyEngine<T>&& other) = delete;
    };

} // namespace BeaconTech::Strategies

// ********** Template Definitions **********
#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYENGINE_CPP
#include "StrategyEngine.cpp"
#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYENGINE_CPP

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYENGINE_HPP
