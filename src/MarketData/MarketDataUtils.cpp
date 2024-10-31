//
// Common utilities used by market data components
//
// Created by Michael Lewis on 10/2/23.
//

#include <iomanip>
#include <ios>
#include <string>

#include <boost/format.hpp>

#include <databento/historical.hpp>
#include <databento/live.hpp>
#include <databento/exceptions.hpp>
#include <databento/log.hpp>
#include <databento/flag_set.hpp>

#include "MarketDataUtils.hpp"
#include "CommonServer/utils/ConfigManager.hpp"

using namespace std::chrono_literals;

namespace BeaconTech::MarketData
{

    MarketDataUtils::MarketDataUtils()
    {
        clock.start();
    }

    // Build the market data client. Retry up to a maximum of 10 times before throwing an error
    databento::Historical MarketDataUtils::getHistoricalClient()
    {
        unsigned int attempts = 0;
        while (true)
        {
            try
            {
                ++attempts;
                return databento::HistoricalBuilder{}
                        .SetKey(Common::ConfigManager::stringConfigValueDefaultIfNull("dbnApiKey", ""))
                        .Build();
            }
            catch (const databento::HttpResponseError& e)
            {
                std::string msg = "Unable to connect to market data client - Attempt="
                        + std::to_string(attempts) + ": " + e.what();
                LOGGER.logWarn(CLASS, "getHistoricalClient", msg.c_str());
                if (attempts == 10)
                {
                    LOGGER.logSevere(CLASS, "getHistoricalClient", "Exceeded max attempts connecting to market data provider");
                    throw e;
                }
            }
            catch (const std::exception& e)
            {
                std::string msg = "Unable to connect to market data client - Attempt="
                        + std::to_string(attempts) + ": " + e.what();
                LOGGER.logWarn(CLASS, "getHistoricalClient", msg.c_str());
                if (attempts == 10)
                {
                    LOGGER.logSevere(CLASS, "getHistoricalClient", "Exceeded max attempts connecting to market data provider");
                    throw e;
                }
            }

            try
            {
                // Sleep before retrying to allow any potential network issues to recover
                std::this_thread::sleep_for(10s);
            }
            catch (const std::exception& e)
            {
                std::string msg = "Unable to connect to market data client - Attempt="
                        + std::to_string(attempts) + ": " + e.what();
                LOGGER.logWarn(CLASS, "getHistoricalClient", msg.c_str());
            }
        }
    }

    // Build the market data client. Retry up to a maximum of 10 times before throwing an error
    databento::LiveBlocking MarketDataUtils::getLiveClient()
    {
        unsigned int attempts = 0;
        while (true)
        {
            try
            {
                ++attempts;
                // todo Implement live data feeds after backtesting strategies. See link below for more info
                // https://docs.databento.com/api-reference-live/client?historical=cpp&live=cpp
                return databento::LiveBuilder{}
                        .SetKeyFromEnv()  // `DATABENTO_API_KEY` environment variable
                        .SetDataset("")
                        .BuildBlocking();
            }
            catch (const databento::HttpResponseError& e)
            {
                std::string msg = "Unable to connect to market data client - Attempt="
                        + std::to_string(attempts) + ": " + e.what();
                LOGGER.logWarn(CLASS, "getLiveClient", msg.c_str());
                if (attempts == 10)
                {
                    LOGGER.logSevere(CLASS, "getLiveClient", "Exceeded max attempts connecting to market data provider");
                    throw e;
                }
            }
            catch (const std::exception& e)
            {
                std::string msg = "Unable to connect to market data client - Attempt="
                        + std::to_string(attempts) + ": " + e.what();
                LOGGER.logWarn(CLASS, "getLiveClient", msg.c_str());
                if (attempts == 10)
                {
                    LOGGER.logSevere(CLASS, "getLiveClient", "Exceeded max attempts connecting to market data provider");
                    throw e;
                }
            }

            try
            {
                // Sleep before retrying to allow any potential network issues to recover
                std::this_thread::sleep_for(10s);
            }
            catch (const std::exception& e)
            {
                std::string msg = "Unable to connect to market data client - Attempt="
                        + std::to_string(attempts) + e.what();
                LOGGER.logWarn(CLASS, "getLiveClient", msg.c_str());
            }
        }
    }

    // Helper function used to determine which mode to run in
    std::string MarketDataUtils::getEnvironmentType()
    {
        return Common::ConfigManager::stringConfigValueDefaultIfNull("environmentType", "Dev");
    }

    // Used to partition the system into multiple symbol ranged engines (aka threads)
    unsigned int MarketDataUtils::getNumThreads()
    {
        return Common::ConfigManager::intConfigValueDefaultIfNull("numThreads", 1);
    }

    // True if the flag is set. False otherwise
    bool MarketDataUtils::isFlagSet(const databento::FlagSet& flag, std::uint8_t bit)
    {
        return (flag & bit) == bit;
    }

    // Prints best bid and ask for each book after processing the last message in the packet
    void MarketDataUtils::printBbo(const Common::Bbo& bbo, const double& fairMarketPrice)
    {
        ++counter;
        if (counter % 1'000'000 == 0)
        {
            clock.stop();
            LOGGER.logInfo(CLASS, "printBbo", "Microseconds=% startTime=% stopTime=%",
                           clock.elapsedTime(), clock.getStartTime().time_since_epoch().count(),
                           clock.getStopTime().time_since_epoch().count());
            clock.start();
        }

        if (!Common::ConfigManager::boolConfigValueDefaultIfNull("printBbo", false)) return;

        std::uint32_t instrumentId;
        MarketData::PriceLevel bestBid{};
        MarketData::PriceLevel bestAsk{};

        std::tie(instrumentId, bestBid, bestAsk) = bbo;

//        LOGGER.logInfo(CLASS, "printBbo", "InstrumentId=% bestBid=$% x % bestAsk=$% x % fairPrice=$%",
//                       instrumentId, bestBid.price, bestBid.size, bestAsk.price, bestAsk.size, fairMarketPrice);
//        auto formattedBid = boost::format("Best bid: %1% × %2%") % bestBid.price % bestBid.size;
//        auto formattedAsk = boost::format("Best ask: %1% × %2%") % bestAsk.price % bestAsk.size;
//        auto formattedFairPrice = boost::format("Fair market price: %1%") % fairMarketPrice;

//        std::cout << std::left << std::setfill(' ')
//                  << "InstrumentId: " << std::setw(12) << instrumentId
//                  << std::setw(28)
//                  << formattedBid.str()
//                  << std::setw(28)
//                  << formattedAsk.str()
//                  << formattedFairPrice.str()
//                  << std::endl;
    }
} // namespace BeaconTech::marketdata