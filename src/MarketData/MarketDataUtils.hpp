//
// Created by Michael Lewis on 9/28/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAUTILS_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAUTILS_HPP

#include <iostream>
#include <exception>
#include <thread>

#include <databento/historical.hpp>
#include <databento/live.hpp>
#include <databento/exceptions.hpp>
#include <databento/log.hpp>
#include <nlohmann/json.hpp>

#include "../Resources/ConfigReader.hpp"

using namespace std::chrono_literals;

class MarketDataUtils
{
private:
    static void logErrorMessage(int attempt, const std::string& what)
    {
        std::cerr << "Unable to connect to market data provider on attempt=" << attempt << what << std::endl;
    }

public:

     // Build the market data provider client. Retry up to a maximum of 10 times before throwing an error
    static databento::Historical getHistoricalClient()
    {
        int attempts = 0;
        while (true)
        {
            try
            {
                ++attempts;
                return HistoricalBuilder{}.SetKey(ConfigReader::extractStringValueFromConfig("dbnApiKey")).Build();
            }
            catch (const HttpResponseError& e)
            {
                logErrorMessage(attempts, e.what());
                if (attempts == 10)
                {
                    throw e;
                }
            }
            catch (const std::exception& e)
            {
                logErrorMessage(attempts, e.what());
                if (attempts == 10)
                {
                    throw e;
                }
            }

            try
            {
                std::this_thread::sleep_for(10s);
            }
            catch (const std::exception& e)
            {
                logErrorMessage(attempts, e.what());
            }
        }
    }

    // Build the market data provider client. Retry up to a maximum of 10 times before throwing an error
    static databento::LiveBlocking getLiveClient()
    {
        int attempts = 0;
        while (true)
        {
            try
            {
                ++attempts;
                // todo Implement live data feeds after backtesting strategies. See link below to determine
                // blocking versus threaded strategy
                // https://docs.databento.com/api-reference-live/client?historical=cpp&live=cpp
                return LiveBuilder{}
                        .SetKeyFromEnv()  // `DATABENTO_API_KEY` environment variable
                        .SetDataset("")
                        .BuildBlocking();
            }
            catch (const HttpResponseError& e)
            {
                logErrorMessage(attempts, e.what());
                if (attempts == 10)
                {
                    throw e;
                }
            }
            catch (const std::exception& e)
            {
                logErrorMessage(attempts, e.what());
                if (attempts == 10)
                {
                    throw e;
                }
            }

            try
            {
                std::this_thread::sleep_for(10s);
            }
            catch (const std::exception& e)
            {
                logErrorMessage(attempts, e.what());
            }
        }
    }
};

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAUTILS_HPP
