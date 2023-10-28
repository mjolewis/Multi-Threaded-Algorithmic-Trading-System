//
// Loads configs from a JSON file into a highly efficient unordered map that can be accessed
// by all system components to customize runtime behavior
//
// Created by Michael Lewis on 9/29/23.
//

#include <cctype>
#include <algorithm>
#include <fstream>
#include <exception>
#include <iostream>

#include <nlohmann/json.hpp>

#include "ConfigManager.hpp"
#include "src/CommonServer/Logging/LogLevel.hpp"

using json = nlohmann::json;

namespace BeaconTech::Common
{
    // Loads a JSON formatted config file and builds an unordered map from the key-value pair
    void ConfigManager::loadDefaultConfigs()
    {
        try
        {
            static std::ifstream configFile{filePath, std::ios::in};
            static nlohmann::json json = json::parse(configFile);

            // Uses structured binding to access the key:value pair from the object
            for (auto& [key, val] : json.items())
            {
                configs.emplace(key, val);
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << Common::LogLevel::SEVERE.getDesc()
                      << " : Unable to load default configs - " << e.what() << std::endl;
        }
    }

    // Extracts a string value from the config. Default if null
    std::string ConfigManager::stringConfigValueDefaultIfNull(const std::string& configName, const std::string& defaultValue)
    {
        auto config = configs.find(configName);
        return config == configs.cend() ? defaultValue : config->second;
    }

    // Extracts a string value from the config and converts it into a bool. Default if null
    bool ConfigManager::boolConfigValueDefaultIfNull(const std::string& configName, const bool& defaultValue)
    {
        auto config = configs.find(configName);
        const std::string& testValue = "true";
        return std::equal(config->second.cbegin(), config->second.cend(),
                                   testValue.cbegin(), testValue.cend(),
                                   [&](char lhs, char rhs) { return std::tolower(lhs) == std::tolower(rhs); } );
    }

    // Extracts a string value from the config and converts it into an int. Default if null
    int ConfigManager::intConfigValueDefaultIfNull(const std::string& configName, const int& defaultValue)
    {
        auto config = configs.find(configName);
        return config == configs.cend() ? defaultValue : std::stoi(config->second);
    }

    // Extracts a string value from the config and converts it into a double. Default if null
    double ConfigManager::doubleConfigValueDefaultIfNull(const std::string& configName, const double& defaultValue)
    {
        auto config = configs.find(configName);
        return config == configs.cend() ? defaultValue : std::stod(config->second);
    }
} // namespace BeaconTech::Common