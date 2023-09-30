//
// Created by Michael Lewis on 9/29/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CONFIGREADER_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CONFIGREADER_HPP

#include <fstream>
#include <string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ConfigReader
{
private:
    inline static std::ifstream configFile{"../src/Resources/config.json"};
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
};

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CONFIGREADER_HPP
