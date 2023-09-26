/*
 * Represents a base class for market data entities such as quotes, orders, and trades
 */

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MDENTITY_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MDENTITY_HPP

#include <string>

class MdEntity
{
private:
    std::string symbol;
    long exchangeTimestamp;
    int tradeDate;

public:
    MdEntity(MdEntity mdEntity);
    ~MdEntity() = default;

    std::string MdEntity::getSymbol();
    void MdEntity::setSymbol(const std::string& symbol);

    long MdEntity::getExchangeTimestamp();
    void MdEntity::setExchangeTimestamp(long exchangeTimestamp);

    int MdEntity::getTradeDate();
    void MdEntity::setTradeDate(int tradeDate);
};

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MDENTITY_HPP
