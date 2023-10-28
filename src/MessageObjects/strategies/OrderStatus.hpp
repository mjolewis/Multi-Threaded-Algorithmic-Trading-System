//
// A data structure to represent FIX tag 150.
//
// Identifies current status of order.
//
// Created by Michael Lewis on 10/28/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERSTATUS_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERSTATUS_HPP

#include "CommonServer/datastructures/AbstractCodes.hpp"

namespace BeaconTech::Strategies
{

    class OrderStatus : public Common::AbstractCodes
    {
        char fixCode;

        OrderStatus(int32_t id, std::string desc, char fixCode) : AbstractCodes{id, std::move(desc)}, fixCode{fixCode} {}

    public:

        // Enum Declarations
        static const OrderStatus SUBMIT_PENDING;
        static const OrderStatus OPEN;

        static const OrderStatus REPLACE_PENDING;

        static const OrderStatus CANCEL_PENDING;
        static const OrderStatus CANCELLED;

        static const OrderStatus PARTIAL_FILL;
        static const OrderStatus FILLED;

        static const OrderStatus UNKNOWN;

        bool operator==(const OrderStatus& other) const noexcept
        {
            return fixCode == other.fixCode;
        }

        // todo - Implement caching logic to look up codes by id
        static const std::map<int32_t, Common::AbstractCodes> CODES_BY_ID;

        inline char getFixCode() const { return fixCode; }

        inline static OrderStatus fromFix(char fixCode_, int32_t id)
        {
            switch(fixCode_)
            {
                case 'A':
                    return SUBMIT_PENDING;
                case '0':
                    return OPEN;
                case 'E':
                    return REPLACE_PENDING;
                case '6':
                    return CANCEL_PENDING;
                case '4':
                    return CANCELLED;
                case '1':
                    return PARTIAL_FILL;
                case '2':
                    return FILLED;
                default:
                    return UNKNOWN;
            }
        }
    };

    // Enum Definitions
    inline const OrderStatus OrderStatus::SUBMIT_PENDING = OrderStatus{1, "Submit Pending", 'A'};
    inline const OrderStatus OrderStatus::OPEN = OrderStatus{2, "Open", '0'};
    inline const OrderStatus OrderStatus::REPLACE_PENDING = OrderStatus{3, "Replace Pending", 'E'};
    inline const OrderStatus OrderStatus::CANCEL_PENDING = OrderStatus{4, "Cancel Pending", '6'};
    inline const OrderStatus OrderStatus::CANCELLED = OrderStatus{5, "Cancelled", '4'};
    inline const OrderStatus OrderStatus::PARTIAL_FILL = OrderStatus{6, "Partial Fill", '1'};
    inline const OrderStatus OrderStatus::FILLED = OrderStatus{7, "Filled", '2'};
    inline const OrderStatus OrderStatus::UNKNOWN = OrderStatus{8, "Unknown", ' '};

} // BeaconTech::Strategies

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERSTATUS_HPP
