//
// Created by Michael Lewis on 9/28/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAUTILS_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAUTILS_HPP

#include <string>

#include <databento/historical.hpp>
#include <databento/live.hpp>
#include <databento/exceptions.hpp>
#include <databento/log.hpp>
#include <nlohmann/json.hpp>

namespace MarketData
{
    class MarketDataUtils
    {
    private:
        static void logErrorMessage(int attempt, const std::string& what);

    public:
        static databento::Historical getHistoricalClient();
        static databento::LiveBlocking getLiveClient();
        static std::string getEnvironmentType();
    };
}

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAUTILS_HPP
