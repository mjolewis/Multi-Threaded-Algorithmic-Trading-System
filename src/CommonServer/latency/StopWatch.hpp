//
// A simple utility class to measure elapsed time. Typical use cases are for profiling the
// running time of algorithms.
//
// Created by Michael Lewis on 7/6/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STOPWATCH_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STOPWATCH_HPP

#include <chrono>

#include "src/CommonServer/TypeSystem/DateTimes.hpp"

namespace BeaconTech::Common
{
    class StopWatch
    {
    private:
        TimePoint startTime;
        TimePoint stopTime;

        StopWatch(const StopWatch &);
        StopWatch & operator=(const StopWatch &);

    public:
        StopWatch() = default;

        void start();

        void stop();

        void reset();

        double elapsedTime() const;
    };

} // namespace BeaconTech::Utils


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_STOPWATCH_HPP
