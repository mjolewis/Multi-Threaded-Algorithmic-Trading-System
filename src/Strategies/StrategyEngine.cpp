//
// A high-performance and lock free engine model with deterministic message processing.
//
// Created by Michael Lewis on 10/4/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYENGINE_CPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYENGINE_CPP

#include <iostream>
#include <memory>

#include "StrategyEngine.hpp"
#include "StrategyServer.hpp"
#include "CommonServer/Utils/BTConcepts.hpp"

namespace BeaconTech::Strategies
{
    template<typename T>
    StrategyEngine<T>::StrategyEngine(std::shared_ptr<StrategyServer<T>> server, int threadId)
        : server{server}, threadId{threadId}
    {

    }

    template<typename T>
    void StrategyEngine<T>::handle(const std::shared_ptr<Bbos>& bbos)
    {
        std::cout << "Received bbo in strategy engine - ID_" << std::this_thread::get_id()
        << " - ListenerId_" << threadId << std::endl;
    }

} // namespace BeaconTech::Strategies


#endif