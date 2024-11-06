//
// Acts as a temporary utility to identify the types of log levels throughout the system.
// The system should eventually be upgraded to use a low-latency custom-built or 3rd party
// logging library
//
// Created by Michael Lewis on 10/6/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_LOGLEVEL_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_LOGLEVEL_HPP

#include "../datastructures/AbstractCodes.hpp"

namespace BeaconTech::Common
{
    class LogLevel : public Common::AbstractCodes
    {
    private:
        LogLevel(int32_t id, std::string desc) : Common::AbstractCodes(id, std::move(desc)) {}

    public:
        LogLevel() = default;

        // Enum declarations
        static const LogLevel INFO;
        static const LogLevel WARN;
        static const LogLevel SEVERE;
    };

    // Enum definitions
    inline const LogLevel LogLevel::INFO = LogLevel{1, "INFO"};
    inline const LogLevel LogLevel::WARN = LogLevel{2, "WARN"};
    inline const LogLevel LogLevel::SEVERE = LogLevel{3, "ERROR"};

} // namespace BeaconTech::Common


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_LOGLEVEL_HPP
