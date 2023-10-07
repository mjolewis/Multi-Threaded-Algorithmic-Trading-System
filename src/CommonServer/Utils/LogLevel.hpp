//
// Acts as a temporary utility to identify the types of log levels throughout the system.
// The system should eventually be upgraded to use a low-latency custom-built or 3rd party
// logging library
//
// Created by Michael Lewis on 10/6/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_LOGLEVEL_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_LOGLEVEL_HPP

#include "src/DataStructures/AbstractCodes.hpp"

namespace BeaconTech::Utils
{
    class LogLevel : public DataStructures::AbstractCodes
    {
    private:
        LogLevel(int id, std::string desc) : AbstractCodes(id, std::move(desc)) {}

    public:
        LogLevel() = default;

        // Enum declarations
        static const LogLevel INFO;
        static const LogLevel WARN;
        static const LogLevel SEVERE;

        // todo - Implement caching logic to look up codes by id
        static const std::map<int, AbstractCodes> CODES_BY_ID;
    };

    // Enum definitions
    inline const LogLevel LogLevel::INFO = LogLevel{1, "Info"};
    inline const LogLevel LogLevel::WARN = LogLevel{2, "Warn"};
    inline const LogLevel LogLevel::SEVERE = LogLevel{3, "Severe"};

} // namespace BeaconTech::Utils


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_LOGLEVEL_HPP
