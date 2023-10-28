//
// A data structure that the PositionManager uses to track the current positions and PnL
// for a given instrument id.
//
// Created by Michael Lewis on 10/28/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_POSITIONINFO_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_POSITIONINFO_HPP

#include <string>

namespace BeachTech::Strategies
{

    struct PositionInfo
    {
        uint32_t instrumentId{0};  // todo upgrade to isin after building a symbol resolver
        uint32_t tradeDate{0};
        int32_t position{0};     // Represents the qty of all trades
        int32_t buyInterest{0};  // Represents the qty of a pending + open order
        int32_t sellInterest{0}; // Represents the qty of a pending + open order
        double realizedPnl{0};
        double unrealizedPnl{0};
        double totalPnl{0};
        int32_t version{0};
    };

} // namespace BeaconTech::Strategies

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_POSITIONINFO_HPP
