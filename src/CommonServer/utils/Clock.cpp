//
// A simple utility class to measure elapsed time. Typical use cases are for profiling the
// running time of algorithms.
//
// Created by Michael Lewis on 7/6/23.
//

#include <chrono>

#include "Clock.hpp"

namespace BeaconTech::Common
{
    Clock::Clock() : tradeDate_{std::chrono::sys_days{std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now())}}
    {

    }

    void Clock::start()
    {
        startTime = std::chrono::steady_clock::now();
    }

    void Clock::stop()
    {
        stopTime = std::chrono::steady_clock::now();
    }

    void Clock::reset()
    {
        stopTime = startTime = std::chrono::steady_clock::now();
    }

    //Calculates the difference between the stop time and start time
    double Clock::elapsedTime() const
    {
        auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);

        return std::chrono::duration<double>(elapsedTime).count();
    }

    const TradeDate& Clock::tradeDate() const
    {
        return tradeDate_;
    }

    TimePoint Clock::createTime()
    {
        return std::chrono::steady_clock::now();
    }

} // namespace BeaconTech::utils
