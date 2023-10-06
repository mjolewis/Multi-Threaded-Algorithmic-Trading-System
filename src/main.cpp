//
// Created by Michael Lewis on 9/28/23.
//

#include "src/MarketData/Clients/MarketDataHistoricalClient.hpp"
#include "src/MarketData/Clients/MarketDataLiveClient.hpp"

int main()
{
    MarketData::MarketDataHistoricalClient marketDataClient{"main"};
    marketDataClient.stop();
    return 0;
}
