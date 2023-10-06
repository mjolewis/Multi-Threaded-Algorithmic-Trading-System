//
// Created by Michael Lewis on 10/2/23.
//

#include <string>

#include <databento/historical.hpp>
#include <databento/live.hpp>
#include <databento/exceptions.hpp>
#include <databento/log.hpp>
#include <nlohmann/json.hpp>

#include "MarketDataUtils.hpp"
#include "../Resources/ConfigReader.hpp"
#include "src/CommonServer/Utils/LogLevel.hpp"

using namespace std::chrono_literals;

namespace MarketData
{
    // Logging utility. Will eventually need to convert to a low-latency custom-built or 3rd party logging library
    void MarketDataUtils::log(const Utilities::LogLevel& logLevel, const std::string& message)
    {
        std::cerr << logLevel.getDesc() << " : " << message << std::endl;
    }

    // Build the market data client. Retry up to a maximum of 10 times before throwing an error
    databento::Historical MarketDataUtils::getHistoricalClient()
    {
        int attempts = 0;
        while (true)
        {
            try
            {
                ++attempts;
                return databento::HistoricalBuilder{}
                        .SetKey(Utilities::ConfigReader::extractStringValueFromConfig("dbnApiKey"))
                        .Build();
            }
            catch (const databento::HttpResponseError& e)
            {
                std::string msg = "Unable to connect to market data client - Attempt=" + std::to_string(attempts);
                log(Utilities::LogLevel::WARN, msg + " : " + e.what());
                if (attempts == 10)
                {
                    log(Utilities::LogLevel::SEVERE, "Exceeded max attempts connecting to market data provider");
                    throw e;
                }
            }
            catch (const std::exception& e)
            {
                std::string msg = "Unable to connect to market data client - Attempt=" + std::to_string(attempts);
                log(Utilities::LogLevel::WARN, msg + " : " + e.what());
                if (attempts == 10)
                {
                    log(Utilities::LogLevel::SEVERE, "Exceeded max attempts connecting to market data provider");
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
                std::string msg = "Unable to connect to market data client - Attempt=" + std::to_string(attempts);
                log(Utilities::LogLevel::WARN, msg + " : " + e.what());
            }
        }
    }

    // Build the market data client. Retry up to a maximum of 10 times before throwing an error
    databento::LiveBlocking MarketDataUtils::getLiveClient()
    {
        int attempts = 0;
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
                std::string msg = "Unable to connect to market data client - Attempt=" + std::to_string(attempts);
                log(Utilities::LogLevel::WARN, msg + " : " + e.what());
                if (attempts == 10)
                {
                    log(Utilities::LogLevel::SEVERE, "Exceeded max attempts connecting to market data provider");
                    throw e;
                }
            }
            catch (const std::exception& e)
            {
                std::string msg = "Unable to connect to market data client - Attempt=" + std::to_string(attempts);
                log(Utilities::LogLevel::WARN, msg + " : " + e.what());
                if (attempts == 10)
                {
                    log(Utilities::LogLevel::SEVERE, "Exceeded max attempts connecting to market data provider");
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
                std::string msg = "Unable to connect to market data client - Attempt=" + std::to_string(attempts);
                log(Utilities::LogLevel::WARN, msg + " : " + e.what());
            }
        }
    }

    // Helper function used to determine which mode to run in
    std::string MarketDataUtils::getEnvironmentType()
    {
        return Utilities::ConfigReader::extractStringValueFromConfig("environmentType");
    }

    // Used to partition the system into multiple symbol ranged engines (aka threads)
    int MarketDataUtils::getThreadCount()
    {
        return Utilities::ConfigReader::extractIntValueFromConfig("threadCount");
    }
}