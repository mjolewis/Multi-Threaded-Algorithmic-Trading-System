//
// The system will operate across various environments such as back-testing, dev, qa, and prod.
// Each of these environments will ultimately have their own infrastructure (e.g. servers, databases, etc.).
// As a result, the environment is configurable via this data structure.
//
// Created by Michael Lewis on 9/29/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ENVIRONMENTTYPE_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ENVIRONMENTTYPE_HPP

#include <map>

#include "CommonServer/datastructures/AbstractCodes.hpp"

namespace BeaconTech::MessageObjects
{
    class EnvironmentType : public Common::AbstractCodes
        {
        private:
            EnvironmentType(int32_t id, std::string desc) : AbstractCodes(id, std::move(desc)) {}

        public:
            EnvironmentType() = default;

            // Enum declarations
            static const EnvironmentType TEST;
            static const EnvironmentType DEV;
            static const EnvironmentType QA;
            static const EnvironmentType PROD;

            // todo - Implement caching logic to look up codes by id
            static const std::map<int32_t, AbstractCodes> CODES_BY_ID;
        };

    // Enum definitions
    inline const EnvironmentType EnvironmentType::TEST = EnvironmentType{1, "Test"};
    inline const EnvironmentType EnvironmentType::DEV = EnvironmentType{2, "Dev"};
    inline const EnvironmentType EnvironmentType::QA = EnvironmentType{3, "Qa"};
    inline const EnvironmentType EnvironmentType::PROD = EnvironmentType{3, "Prod"};
}


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ENVIRONMENTTYPE_HPP
