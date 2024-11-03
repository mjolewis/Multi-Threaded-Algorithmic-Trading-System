//
// Common utilities used by market data components
//
// Created by Michael Lewis on 10/2/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAUTILS_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAUTILS_HPP

#define CLASS_FILE_PATH (std::filesystem::path(__FILE__).parent_path().string())

#include <string>
#include <utility>

#include <databento/historical.hpp>
#include <databento/live.hpp>
#include <databento/exceptions.hpp>
#include <databento/flag_set.hpp>
#include <nlohmann/json.hpp>

#include "OrderBook.hpp"
#include "MessageObjects/marketdata/PriceLevel.hpp"
#include "CommonServer/logging/Logger.hpp"

namespace BeaconTech::MarketData
{

    class MarketDataUtils
    {
    private:
        inline static const std::string CLASS_PATH = CLASS_FILE_PATH;
        inline static const std::string APP_NAME = "MARKETDATA";
        inline static const std::string CLASS = "MARKETDATAUTILS";
        inline static BeaconTech::Common::Logger LOGGER{CLASS_PATH, APP_NAME, 0};
        inline static BeaconTech::Common::Clock clock{};
        inline static int counter = 0;

    public:
        MarketDataUtils();

        static databento::Historical getHistoricalClient();

        static databento::LiveBlocking getLiveClient();

        static std::string getEnvironmentType();

        static unsigned int getNumThreads();

        static bool isFlagSet(const databento::FlagSet& flag, std::uint8_t bit);

        static void printBbo(const Common::Bbo& bbo, const double& fairMarketPrice);
    };
} // namespace BeaconTech::marketdata


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAUTILS_HPP
