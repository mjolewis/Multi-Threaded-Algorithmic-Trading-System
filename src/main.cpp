//
// Created by Michael Lewis on 9/28/23.
//

#include <iostream>

#include "CommonServer/utils/ConfigManager.hpp"
#include "MarketData/clients/MarketDataHistoricalClient.hpp"
#include "MarketData/clients/MarketDataLiveClient.hpp"
#include "Strategies/StrategyServer.hpp"

int main()
{
    using Client = BeaconTech::MarketData::MarketDataHistoricalClient;

    BeaconTech::Common::ConfigManager::loadDefaultConfigs();
    BeaconTech::Strategies::StrategyServer<Client> server{};
    return 0;
}
