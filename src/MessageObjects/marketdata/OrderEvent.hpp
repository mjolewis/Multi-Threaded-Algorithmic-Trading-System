//
// Represents FIX tag 150
//
// Created by Michael Lewis on 11/17/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDEREVENT_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDEREVENT_HPP

#include <utility>

#include "../../CommonServer/datastructures/AbstractCodes.hpp"

namespace BeaconTech::MarketData
{

    class OrderEvent : public Common::AbstractCodes
    {
    private:
        char fixCode;

        OrderEvent(int8_t id, std::string desc, char fixCode) : Common::AbstractCodes(id, std::move(desc)), fixCode{fixCode} {}

    public:

        // Enum Declarations
        static const OrderEvent SUBMIT;
        static const OrderEvent SUBMIT_REJECTED;
        static const OrderEvent SUBMITTED;

        static const OrderEvent CANCEL;
        static const OrderEvent CANCEL_REJECTED;
        static const OrderEvent CANCELLED;

        static const OrderEvent REPLACE;
        static const OrderEvent REPLACE_REJECTED;
        static const OrderEvent REPLACED;

        static const OrderEvent FILL;

        static const OrderEvent INVALID;

        inline char getFixCode() const { return fixCode; }
    };

    // Enum Definitions
    inline const OrderEvent OrderEvent::SUBMIT = OrderEvent{1, "SUBMIT", 'A'};
    inline const OrderEvent OrderEvent::SUBMIT_REJECTED = OrderEvent{2, "SUBMIT_REJECTED", '8'};
    inline const OrderEvent OrderEvent::SUBMITTED = OrderEvent{3, "SUBMITTED", '0'};

    inline const OrderEvent OrderEvent::CANCEL = OrderEvent{4, "CANCEL", '6'};
    inline const OrderEvent OrderEvent::CANCEL_REJECTED = OrderEvent{5, "CANCEL_REJECTED", '8'};
    inline const OrderEvent OrderEvent::CANCELLED = OrderEvent{6, "CANCELLED", '4'};

    inline const OrderEvent OrderEvent::REPLACE = OrderEvent{7, "REPLACE", 'E'};
    inline const OrderEvent OrderEvent::REPLACE_REJECTED = OrderEvent{8, "REPLACE_REJECTED", '8'};
    inline const OrderEvent OrderEvent::REPLACED = OrderEvent{9, "REPLACED", '5'};

    inline const OrderEvent OrderEvent::FILL = OrderEvent{10, "FILL", '2'};

    inline const OrderEvent OrderEvent::INVALID = OrderEvent{11, "INVALID", ' '};

} //namespace BeaconTech::MarketData

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDEREVENT_HPP
