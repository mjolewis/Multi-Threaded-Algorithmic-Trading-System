//
// Created by Michael Lewis on 12/20/23.
//

#include "../CommonServer/utils/ConfigManager.hpp"
#include "../MarketData/clients/MarketDataHistoricalClient.hpp"
#include "StrategyServer.hpp"

int main()
{
    using Client = BeaconTech::MarketData::MarketDataHistoricalClient;

    BeaconTech::Common::ConfigManager::loadDefaultConfigs();
    BeaconTech::Strategies::StrategyServer<Client> server{};

    return 0;
}