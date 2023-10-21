//
// Represents a base class for data structures that need to be encoded and decoded for efficient persistence
// and/or message passing between components
//
// Created by Michael Lewis on 9/29/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ABSTRACTCODES_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ABSTRACTCODES_HPP

#include "string"
#include "map"

namespace BeaconTech::Common
{
    class AbstractCodes
    {
    private:
        int id{};
        std::string desc;

    protected:
        AbstractCodes(int id, std::string desc)
        {
            this->id = id;
            this->desc = std::move(desc);
        }

    public:
        AbstractCodes() = default;

        virtual ~AbstractCodes() = default;

        inline virtual std::string getDesc() const {return this->desc;}

        inline virtual constexpr explicit operator int() const {return id;}
    };
}

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_ABSTRACTCODES_HPP
