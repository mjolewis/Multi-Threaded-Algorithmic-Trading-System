//
// Created by Michael Lewis on 9/28/23.
//

#include "CommonServer/Utils/ConfigManager.hpp"
#include "MarketData/Clients/MarketDataHistoricalClient.hpp"
#include "MarketData/Clients/MarketDataLiveClient.hpp"
#include "Strategies/StrategyServer.hpp"

int main()
{
    using Client = BeaconTech::MarketData::MarketDataHistoricalClient;

    BeaconTech::Utils::ConfigManager::loadDefaultConfigs();
    BeaconTech::Strategies::StrategyServer<Client> server{};
//    BeaconTech::MarketData::MarketDataHistoricalClient marketDataClient{"main"};
//    marketDataClient.stop();
    return 0;
}
