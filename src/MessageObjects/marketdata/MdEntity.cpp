/*
 * Represents a base class for market data entities such as quotes, orders, and trades
 */

#include "MdEntity.hpp"
#include "../../CommonServer/types/DateTimes.hpp"

namespace BeaconTech::MarketData
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

    Common::UnixNanos MdEntity::getExchangeTimestamp()
    {
        return exchangeTimestamp;
    }

    void MdEntity::setExchangeTimestamp(Common::UnixNanos exchangeTimestamp)
    {
        this->exchangeTimestamp = exchangeTimestamp;
    }

    unsigned int MdEntity::getTradeDate()
    {
        return tradeDate;
    }

    void MdEntity::setTradeDate(unsigned int tradeDate)
    {
        this->tradeDate = tradeDate;
    }
} // namespace BeaconTech::MarketData