//
// A tagged union that represents a single log entry.
// The anonymous union simplifies the definition of the struct with a tag-union pair.
//
// Created by Michael Lewis on 12/18/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_LOGELEMENT_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_LOGELEMENT_HPP

#include "../logging/LogType.hpp"

namespace BeaconTech::Common
{

    struct LogElement
    {
        LogType logType = LogType::CHAR;  // Discriminate (aka tag)
        union  // Anonymous union
        {
            char c;
            int i;
            long l;
            long long ll;
            unsigned u;
            unsigned long ul;
            unsigned long long ull;
            float f;
            double d;
        } u;
    };
}

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_LOGELEMENT_HPP
