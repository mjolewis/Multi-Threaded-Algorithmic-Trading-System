//
// A FIX field to indicate the interest of the participant.
//
// Created by Michael Lewis on 10/6/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_SIDE_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_SIDE_HPP

#include <map>
#include <string>

#include "CommonServer/datastructures/AbstractCodes.hpp"

namespace BeaconTech::MarketData
{

    class Side : public Common::AbstractCodes
    {
    private:
        char fixCode;

        Side(int id, std::string desc, char fixCode) : AbstractCodes{id, std::move(desc)}, fixCode{fixCode} {}

    public:
        Side() : fixCode{} {};

        // Enum Declarations
        static const Side SELL;
        static const Side BUY;
        static const Side UNKNOWN;

        bool operator==(const Side& other) const noexcept
        {
            return fixCode == other.fixCode;
        }

        // todo - Implement caching logic to look up codes by id
        static const std::map<int, Common::AbstractCodes> CODES_BY_ID;

        inline char getFixCode() const { return fixCode; }

        inline static Side fromFix(char fixCode_)
        {
            switch(fixCode_)
            {
                case 'A':
                    return SELL;
                case 'B':
                    return BUY;
                default:
                    return UNKNOWN;
            }
        }
    };

    // Enum Definitions
    inline const Side Side::BUY = Side{1, "Buy", 'B'};
    inline const Side Side::SELL = Side{2, "Sell", 'A'};
    inline const Side Side::UNKNOWN = Side{3, "Unknown", 'N'};

} // namespace BeaconTech::MarketData


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_SIDE_HPP
