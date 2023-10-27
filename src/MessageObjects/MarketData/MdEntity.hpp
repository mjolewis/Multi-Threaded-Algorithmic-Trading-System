/*
 * Represents a base class for market data entities such as quotes, orders, and trades
 */

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MDENTITY_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MDENTITY_HPP

#include <string>
#include "CommonServer/TypeSystem/DateTimes.hpp"

namespace BeaconTech::MessageObjects
{

    class MdEntity
    {
    private:
        std::string symbol;
        Common::UnixNanos exchangeTimestamp;
        int tradeDate;

    public:
        MdEntity() = default;
        MdEntity(const MdEntity& mdEntity);
        virtual ~MdEntity() = default;

        std::string getSymbol();

        void setSymbol(const std::string& symbol);

        Common::UnixNanos getExchangeTimestamp();

        void setExchangeTimestamp(Common::UnixNanos exchangeTimestamp);

        int getTradeDate();

        void setTradeDate(int tradeDate);
    };
}

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MDENTITY_HPP
