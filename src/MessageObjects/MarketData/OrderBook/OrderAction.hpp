//
// A set of actions that trigger an update to the order book.
//
// Created by Michael Lewis on 10/6/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERACTION_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERACTION_HPP

#include <map>
#include <string>

#include "DataStructures/AbstractCodes.hpp"

namespace BeaconTech::MessageObjects
{

    class OrderAction : public DataStructures::AbstractCodes
    {
    private:
        char fixCode;

        OrderAction(int id, std::string desc, char fixCode) : AbstractCodes{id, std::move(desc)}, fixCode{fixCode} {}

    public:
        OrderAction() : fixCode{} {};

        // Enum Declarations
        static const OrderAction ADD;
        static const OrderAction CANCEL;
        static const OrderAction MODIFY;
        static const OrderAction CLEAR;
        static const OrderAction TRADE;
        static const OrderAction FILL;

        // todo - Implement caching logic to look up codes by id
        static const std::map<int, AbstractCodes> CODES_BY_ID;

        inline char getFixCode() const { return fixCode; }
    };

    // Enum Definitions
    inline const OrderAction OrderAction::ADD = OrderAction{1, "Add", 'A'};
    inline const OrderAction OrderAction::CANCEL = OrderAction{2, "Cancel", 'C'};
    inline const OrderAction OrderAction::MODIFY = OrderAction{3, "Modify", 'M'};
    inline const OrderAction OrderAction::CLEAR = OrderAction{4, "Clear", 'R'};
    inline const OrderAction OrderAction::TRADE = OrderAction{5, "Trade", 'T'};
    inline const OrderAction OrderAction::FILL = OrderAction{6, "Fill", 'F'};

} // namespace BeaconTech::MessageObjects


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERACTION_HPP
