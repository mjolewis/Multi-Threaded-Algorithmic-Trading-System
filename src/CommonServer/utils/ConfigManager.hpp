//
// Loads configs from a JSON file into a highly efficient unordered map that can be accessed
// by all system components to customize runtime behavior
//
// Created by Michael Lewis on 9/29/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CONFIGMANAGER_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CONFIGMANAGER_HPP

#include <string>
#include <unordered_map>

namespace BeaconTech::Common
{
    class ConfigManager
    {
    private:
        inline static const std::string filePath = "/Users/mlewis/CLionProjects/Multi-Threaded-Algorithmic-Trading-System/src/CommonServer/resources/config.json";
        inline static std::unordered_map<std::string, std::string> configs{};

    public:
        static void loadDefaultConfigs();

        static std::string stringConfigValueDefaultIfNull(const std::string& configName, const std::string& defaultValue);

        static bool boolConfigValueDefaultIfNull(const std::string& configName, const bool& defaultValue);

        static uint32_t intConfigValueDefaultIfNull(const std::string& configName, const uint32_t& defaultValue);

        static double doubleConfigValueDefaultIfNull(const std::string& configName, const double& defaultValue);
    };
} // namespace BeaconTech::Common


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CONFIGMANAGER_HPP
