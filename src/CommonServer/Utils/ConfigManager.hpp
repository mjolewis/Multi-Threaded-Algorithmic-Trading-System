//
// Loads configs from a JSON file into a highly efficient unordered map that can be accessed
// by all system components to customize runtime behavior
//
// Created by Michael Lewis on 9/29/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CONFIGMANAGER_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CONFIGMANAGER_HPP

#include <fstream>
#include <string>
#include <unordered_map>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace BeaconTech::Utils
{
    class ConfigManager
    {
    private:
        inline static const std::string filePath = "/Users/mlewis/CLionProjects/Multi-Threaded-Algorithmic-Trading-System/src/CommonServer/Utils/Resources/config.json";
        inline static std::unordered_map<std::string, std::string> configs{};

    public:
        static void loadDefaultConfigs();

        static std::string extractStringValueFromConfig(const std::string& key);

        static bool extractBoolValueFromConfig(const std::string& key);

        static int extractIntValueFromConfig(const std::string& key);
    };
} // namespace BeaconTech::Utils


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CONFIGMANAGER_HPP
