//
// Loads configs from a JSON file into a highly efficient unordered map that can be accessed
// by all system components to customize runtime behavior
//
// Created by Michael Lewis on 9/29/23.
//

#include <fstream>
#include <exception>
#include <iostream>

#include <nlohmann/json.hpp>

#include "ConfigManager.hpp"
#include "LogLevel.hpp"

using json = nlohmann::json;

namespace BeaconTech::Utils
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
            std::cerr << Utils::LogLevel::SEVERE.getDesc()
                      << " : Unable to load default configs - " << e.what() << std::endl;
        }
    }

    std::string ConfigManager::stringConfig(const std::string& key)
    {
        return configs.at(key);
    }

    // Extracts a string value from the config and converts it into a bool
    bool ConfigManager::boolConfig(const std::string& key)
    {
        return "true" == configs.at(key);
    }

    // Extracts a string value from the config and converts it into an int
    int ConfigManager::intConfig(const std::string& key)
    {
        return std::stoi(configs.at(key));
    }
} // namespace BeaconTech::Utils