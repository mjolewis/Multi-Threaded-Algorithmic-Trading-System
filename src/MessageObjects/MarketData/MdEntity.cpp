/*
 * Represents a base class for market data entities such as quotes, orders, and trades
 */

#include "MdEntity.hpp"

MdEntity::MdEntity(MdEntity mdEntity)
    : symbol{mdEntity.symbol}, exchangeTimestamp{mdEntity.exchangeTimestamp}, tradeDate{mdEntity.tradeDate}
{

}

std::string MdEntity::getSymbol() { return symbol; }

void MdEntity::setSymbol(const std::string& symbol) { this->symbol = symbol; }

long MdEntity::getExchangeTimestamp() { return exchangeTimestamp; }

void MdEntity::setExchangeTimestamp(long exchangeTimestamp) { this->exchangeTimestamp = exchangeTimestamp; }

int MdEntity::getTradeDate() { return tradeDate; }

void MdEntity::setTradeDate(int tradeDate) { this->tradeDate = tradeDate; }