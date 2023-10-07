//
// Created by Michael Lewis on 9/29/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CONFIGREADER_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CONFIGREADER_HPP

#include <fstream>
#include <string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace BeaconTech::Utils
{
    class ConfigReader
    {
    private:
        inline static const std::string filePath = "/Users/mlewis/CLionProjects/Multi-Threaded-Algorithmic-Trading-System/src/CommonServer/Utils/Resources/config.json";
        inline static std::ifstream configFile{filePath, std::ios::in};
        inline static nlohmann::json data = json::parse(configFile);

    public:
        static std::string extractStringValueFromConfig(const std::string& key)
        {
            return data[key];
        }

        static bool extractBoolValueFromConfig(const std::string& key)
        {
            return data[key];
        }

        static int extractIntValueFromConfig(const std::string& key)
        {
            return data[key];
        }
    };
} // namespace BeaconTech::Utils

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CONFIGREADER_HPP
