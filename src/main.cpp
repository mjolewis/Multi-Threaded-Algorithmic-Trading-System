//
// Created by Michael Lewis on 9/28/23.
//

#include <iostream>

#include "CommonServer/Utils/ConfigManager.hpp"
#include "MarketData/Clients/MarketDataHistoricalClient.hpp"
#include "MarketData/Clients/MarketDataLiveClient.hpp"
#include "Strategies/StrategyServer.hpp"

int main()
{
    using Client = BeaconTech::MarketData::MarketDataHistoricalClient;

    BeaconTech::Common::ConfigManager::loadDefaultConfigs();
    BeaconTech::Strategies::StrategyServer<Client> server{};
    return 0;
}
