//
// Created by Michael Lewis on 10/4/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYENGINE_CPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STRATEGYENGINE_CPP

#include <memory>

#include "StrategyEngine.hpp"
#include "StrategyServer.hpp"

namespace BeaconTech::Strategies
{
    template<typename T>
    StrategyEngine<T>::StrategyEngine(const StrategyServer<T>& server, int threadId)
        : server{std::make_shared<StrategyServer<T>>(server)}, threadId{threadId}
    {

    }

} // namespace BeaconTech::Strategies


#endif