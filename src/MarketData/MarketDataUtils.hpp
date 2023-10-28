//
// Common utilities used by market data components
//
// Created by Michael Lewis on 10/2/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAUTILS_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAUTILS_HPP

#include <string>
#include <utility>

#include <databento/historical.hpp>
#include <databento/live.hpp>
#include <databento/exceptions.hpp>
#include <databento/flag_set.hpp>
#include <nlohmann/json.hpp>

#include "CommonServer/logging/LogLevel.hpp"
#include "OrderBook.hpp"
#include "MessageObjects/marketdata/PriceLevel.hpp"

namespace BeaconTech::MarketData
{

    class MarketDataUtils
    {
    public:
        static void log(const Common::LogLevel& logLevel, const std::string& message);

        static databento::Historical getHistoricalClient();

        static databento::LiveBlocking getLiveClient();

        static std::string getEnvironmentType();

        static int getNumThreads();

        static bool isFlagSet(const databento::FlagSet& flag, std::uint8_t bit);

        static void printBbo(const Common::Bbo& bbo, const double& fairMarketPrice);
    };
} // namespace BeaconTech::marketdata


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAUTILS_HPP
