//
// A simple utility class to measure elapsed time. Typical use cases are for profiling the
// running time of algorithms.
//
// Created by Michael Lewis on 7/6/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CLOCK_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CLOCK_HPP

#include <chrono>

#include "../types/DateTimes.hpp"

namespace BeaconTech::Common
{
    class Clock
    {
    private:
        TimePoint startTime;
        TimePoint stopTime;
        TradeDate tradeDate_;
        UnixNanos timePoint;

    public:
        Clock();

        void start();

        void stop();

        void reset();

        double elapsedTime() const;

        const TradeDate& tradeDate() const;

        const TimePoint& getStartTime() const;

        const TimePoint& getStopTime() const;

        static TimePoint createTime();

        static const std::string getLocalDateAndTime();

        // Deleted default ctors and assignment operators
        Clock(const Clock& other) = delete;

        Clock(Clock&& other) = delete;

        Clock& operator=(const Clock& other) = delete;

        Clock& operator=(Clock&& other) = delete;
    };

} // namespace BeaconTech::utils


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CLOCK_HPP
