/*
 * Represents a base class for market data entities such as quotes, orders, and trades
 */

#include "MdEntity.hpp"
#include "CommonServer/Utils/DataTime.hpp"

namespace BeaconTech::MessageObjects
{
    MdEntity::MdEntity(const MdEntity& mdEntity)
            : symbol{mdEntity.symbol}, exchangeTimestamp{mdEntity.exchangeTimestamp}, tradeDate{mdEntity.tradeDate}
    {

    }

    std::string MdEntity::getSymbol()
    {
        return symbol;
    }

    void MdEntity::setSymbol(const std::string& symbol)
    {
        this->symbol = symbol;
    }

    UnixNanos MdEntity::getExchangeTimestamp()
    {
        return exchangeTimestamp;
    }

    void MdEntity::setExchangeTimestamp(UnixNanos exchangeTimestamp)
    {
        this->exchangeTimestamp = exchangeTimestamp;
    }

    int MdEntity::getTradeDate()
    {
        return tradeDate;
    }

    void MdEntity::setTradeDate(int tradeDate)
    {
        this->tradeDate = tradeDate;
    }
}