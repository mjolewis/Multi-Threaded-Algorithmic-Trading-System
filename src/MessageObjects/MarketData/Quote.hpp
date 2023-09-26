/*
 * A Quote represents tick-by-tick bid or ask interest from participants. This data can be processed off the wire
 * for live trading or via a historical database for back-testing trading strategies.
 */

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_QUOTE_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_QUOTE_HPP

#include <string>

#include "MdEntity.hpp"

class Quote : public MdEntity
{
private:
    double askPrice;
    int askSize;
    double bidPrice;
    int bidSize;
    std::string bidExchange;
    std::string askExchange;

public:
    Quote() = default;
    ~Quote() = default;

    double getAskPrice();
    void setAskPrice(double askPrice);

    int getAskSize();
    void setAskSize(int askSize);

    double getBidPrice();
    void setBidPrice(double bidPrice);

    int getBidSize();
    void setBidSize(int bidSize);

    std::string getBidExchange();
    void setBidExchange(const std::string& bidExchange);

    std::string getAskExchange();
    void setAskExchange(const std::string& askExchange);
};

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_QUOTE_HPP
