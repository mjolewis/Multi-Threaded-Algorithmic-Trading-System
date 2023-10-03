//
// Created by Michael Lewis on 9/29/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ENVIRONMENTTYPE_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ENVIRONMENTTYPE_HPP

#include <map>

#include "../DataStructures/AbstractCodes.hpp"

namespace MessageObjects
{
class EnvironmentType : public DataStructures::AbstractCodes
    {
    private:
        EnvironmentType(int id, std::string desc) : AbstractCodes(id, std::move(desc)) {}

    public:
        EnvironmentType() = default;

        // Enum declarations
        static const EnvironmentType BACKTEST;
        static const EnvironmentType DEV;
        static const EnvironmentType QA;
        static const EnvironmentType PROD;

        // todo - Implement caching logic to look up codes by id
        static const std::map<int, AbstractCodes> CODES_BY_ID;
    };

// Enum definitions
    inline const EnvironmentType EnvironmentType::BACKTEST = EnvironmentType{1, "Backtest"};
    inline const EnvironmentType EnvironmentType::DEV = EnvironmentType{2, "Dev"};
    inline const EnvironmentType EnvironmentType::QA = EnvironmentType{3, "Qa"};
    inline const EnvironmentType EnvironmentType::PROD = EnvironmentType{3, "Prod"};
}


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ENVIRONMENTTYPE_HPP
