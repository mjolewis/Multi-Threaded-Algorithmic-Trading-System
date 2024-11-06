//
// A data structure to represent FIX tag 150.
//
// Describes the specific Execution Report (i.e. Pending Cancel) while OrdStatus <39>
// will always identify the current order status (i.e. Partially Filled)
//
// Created by Michael Lewis on 10/28/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_EXECTYPE_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_EXECTYPE_HPP

#include "../../CommonServer/datastructures/AbstractCodes.hpp"

namespace BeaconTech::Strategies
{

    class ExecType : public Common::AbstractCodes
    {
    private:
        char fixCode;

        ExecType(int32_t id, std::string desc, char fixCode) : AbstractCodes{id, std::move(desc)}, fixCode{fixCode} {}

    public:

        // Enum Declarations
        static const ExecType SUBMIT;
        static const ExecType SUBMIT_REJECTED;
        static const ExecType SUBMITTED;

        static const ExecType REPLACE;
        static const ExecType REPLACE_REJECTED;
        static const ExecType REPLACED;

        static const ExecType CANCEL;
        static const ExecType CANCEL_REJECTED;
        static const ExecType CANCELLED;

        static const ExecType FILL;

        static const ExecType UNKNOWN;

        bool operator==(const ExecType& other) const noexcept
        {
            return fixCode == other.fixCode;
        }

        // todo - Implement caching logic to look up codes by id
        static const std::map<int32_t, Common::AbstractCodes> CODES_BY_ID;

        inline char getFixCode() const { return fixCode; }

        inline static ExecType fromFix(char fixCode_, int32_t id)
        {
            switch(fixCode_)
            {
                case 'A':
                    return SUBMIT;
                case '0':
                    return SUBMITTED;
                case 'E':
                    return REPLACE;
                case '5':
                    return REPLACED;
                case '6':
                    return CANCEL;
                case '4':
                    return CANCELLED;
                case 'F':
                    return FILL;
                case '8':
                    if (id ==  2) return SUBMIT_REJECTED;
                    else if (id == 5) return REPLACE_REJECTED;
                    else if (id == 8) return CANCEL_REJECTED;
                default:
                    return UNKNOWN;
            }
        }
    };

    // Enum Definitions
    inline const ExecType ExecType::SUBMIT = ExecType{1, "Submit", 'A'};
    inline const ExecType ExecType::SUBMIT_REJECTED = ExecType{2, "Submit Rejected", '8'};
    inline const ExecType ExecType::SUBMITTED = ExecType{3, "Submitted", '0'};

    inline const ExecType ExecType::REPLACE = ExecType{4, "Replace", 'E'};
    inline const ExecType ExecType::REPLACE_REJECTED = ExecType{5, "Replace Rejected", '8'};
    inline const ExecType ExecType::REPLACED = ExecType{6, "Replaced", '5'};

    inline const ExecType ExecType::CANCEL = ExecType{7, "Cancel", '6'};
    inline const ExecType ExecType::CANCEL_REJECTED = ExecType{8, "Cancel Rejected", '8'};
    inline const ExecType ExecType::CANCELLED = ExecType{9, "Cancelled", '4'};

    inline const ExecType ExecType::FILL = ExecType{10, "Fill", 'F'};

    inline const ExecType ExecType::UNKNOWN = ExecType{11, "Unknown", ' '};

} // BeaconTech::Strategies

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_EXECTYPE_HPP
