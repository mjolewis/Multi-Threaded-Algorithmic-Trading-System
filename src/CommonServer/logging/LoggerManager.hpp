//
// Created by Michael Lewis on 12/20/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_LOGGERMANAGER_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_LOGGERMANAGER_HPP

#include <memory>
#include <unordered_map>

#include "CommonServer/logging/Logger.hpp"

namespace BeaconTech::Common
{

    class LoggerManager
    {
//    private:
//        static std::unordered_map<std::string, std::unordered_map<std::string, BeaconTech::Common::Logger*>> LOGGERS;
//
//    public:
//
//        static Logger* getLogger(const std::string& className, const std::string& funcName)
//        {
//            auto innerMap = LOGGERS.find(className);
//
//            if (innerMap != LOGGERS.cend())
//            {
//                auto it = innerMap->second.find(funcName);
//                if (it != innerMap->second.cend())
//                {
//                    return it->second;
//                }
//            }
//
//            BeaconTech::Common::Logger* logger = new Logger{className + ".log"};
//            LOGGERS.emplace(className, std::unordered_map<std::string, Logger*>());
//            LOGGERS.at(className).emplace(funcName, logger);
//
//            return logger;
//        }
//    };
}

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_LOGGERMANAGER_HPP
