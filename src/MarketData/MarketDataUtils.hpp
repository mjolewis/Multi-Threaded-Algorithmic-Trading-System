//
// Common utilities used by market data components
//
// Created by Michael Lewis on 10/2/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAUTILS_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAUTILS_HPP

#include <string>

#include <databento/historical.hpp>
#include <databento/live.hpp>
#include <databento/exceptions.hpp>
#include <databento/log.hpp>
#include <databento/flag_set.hpp>
#include <nlohmann/json.hpp>

#include "CommonServer/Utils/LogLevel.hpp"

namespace BeaconTech::MarketData
{
    class MarketDataUtils
    {
    public:
        static void log(const Utils::LogLevel& logLevel, int value, const std::string& message);

        static void log(const Utils::LogLevel& logLevel, const std::string& message);

        static databento::Historical getHistoricalClient();

        static databento::LiveBlocking getLiveClient();

        static std::string getEnvironmentType();

        static int getThreadCount();

        static bool isFlagSet(const databento::FlagSet& flag, std::uint8_t bit);
    };
} // namespace BeaconTech::MarketData

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAUTILS_HPP
