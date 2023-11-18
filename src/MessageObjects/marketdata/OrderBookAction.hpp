//
// A set of actions that trigger an update to the order book.
//
// Created by Michael Lewis on 10/6/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERBOOKACTION_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERBOOKACTION_HPP

#include <map>
#include <string>

#include "CommonServer/datastructures/AbstractCodes.hpp"

namespace BeaconTech::MarketData
{

    class OrderBookAction : public Common::AbstractCodes
    {
    private:
        char fixCode;

        OrderBookAction(int8_t id, std::string desc, char fixCode) : Common::AbstractCodes{id, std::move(desc)}, fixCode{fixCode} {}

    public:
        OrderBookAction() : fixCode{} {};

        // Enum Declarations
        static const OrderBookAction ADD;
        static const OrderBookAction CANCEL;
        static const OrderBookAction MODIFY;
        static const OrderBookAction CLEAR;
        static const OrderBookAction TRADE;
        static const OrderBookAction FILL;

        // todo - Implement caching logic to look up codes by id
        static const std::map<int8_t, Common::AbstractCodes> CODES_BY_ID;

        inline char getFixCode() const { return fixCode; }
    };

    // Enum Definitions
    inline const OrderBookAction OrderBookAction::ADD = OrderBookAction{1, "Add", 'A'};
    inline const OrderBookAction OrderBookAction::CANCEL = OrderBookAction{2, "Cancel", 'C'};
    inline const OrderBookAction OrderBookAction::MODIFY = OrderBookAction{3, "Modify", 'M'};
    inline const OrderBookAction OrderBookAction::CLEAR = OrderBookAction{4, "Clear", 'R'};
    inline const OrderBookAction OrderBookAction::TRADE = OrderBookAction{5, "Trade", 'T'};
    inline const OrderBookAction OrderBookAction::FILL = OrderBookAction{6, "Fill", 'F'};

} // namespace BeaconTech::MarketData


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ORDERBOOKACTION_HPP
