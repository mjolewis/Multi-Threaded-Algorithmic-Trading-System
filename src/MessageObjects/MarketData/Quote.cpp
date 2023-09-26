/*
 * A Quote represents tick-by-tick bid or ask interest from participants. This data can be processed off the wire
 * for live trading or via a historical database for back-testing trading strategies.
 */

#include "Quote.hpp"

double Quote::getAskPrice()
{
    return askPrice;
}

void Quote::setAskPrice(double askPrice)
{
    this->askPrice = askPrice;
}


int Quote::getAskSize()
{
    return askSize;
}

void Quote::setAskSize(int askSize)
{
    this->askSize = askSize;
}

double Quote::getBidPrice()
{
    return bidPrice;
}

void Quote::setBidPrice(double bidPrice)
{
    this->bidPrice = bidPrice;
}

int Quote::getBidSize()
{
    return bidSize;
}

void Quote::setBidSize(int bidSize)
{
    this->bidSize = bidSize;
}

std::string Quote::getBidExchange()
{
    return bidExchange;
}

void Quote::setBidExchange(const std::string &bidExchange)
{
    this->bidExchange = bidExchange;
}

std::string Quote::getAskExchange()
{
    return askExchange;
}

void Quote::setAskExchange(const std::string &askExchange)
{
    this->askExchange = askExchange;
}
