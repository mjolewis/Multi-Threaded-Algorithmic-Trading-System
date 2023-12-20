//
// A simple structure that holds the different types that will be logged by the system.
// LogType is a discriminant for the LogElement to create a type-safe union.
// This is used in favor of std::variant for performance reasons.
//
// Created by Michael Lewis on 12/18/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_LOGTYPE_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_LOGTYPE_HPP

#include <cstddef>
#include <cstdint>

namespace BeaconTech::Common
{
    enum class LogType : std::int8_t
    {
        CHAR = 0,
        INTEGER = 1,
        LONG_INTEGER = 2,
        LONG_LONG_INTEGER = 3,
        UNSIGNED_INTEGER = 4,
        UNSIGNED_LONG_INTEGER = 5,
        UNSIGNED_LONG_LONG_INTEGER = 6,
        FLOAT = 7,
        DOUBLE = 8
    };

} // namespace BeaconTech::Common

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_LOGTYPE_HPP
