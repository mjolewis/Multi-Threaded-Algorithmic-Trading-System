//
// Created by Michael Lewis on 9/28/23.
//

#include "CommonServer/Utils/ConfigManager.hpp"
#include "MarketData/Clients/MarketDataHistoricalClient.hpp"
#include "MarketData/Clients/MarketDataLiveClient.hpp"

int main()
{
    BeaconTech::Utils::ConfigManager::loadDefaultConfigs();
    BeaconTech::MarketData::MarketDataHistoricalClient marketDataClient{"main"};
    marketDataClient.stop();
    return 0;
}
