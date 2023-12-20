//
// A simple utility class to measure elapsed time. Typical use cases are for profiling the
// running time of algorithms.
//
// Created by Michael Lewis on 7/6/23.
//

#include <chrono>
#include <iostream>
#include <sstream>
#include <iomanip>

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

    const std::string Clock::getLocalDateAndTime()
    {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
//            auto tm = *std::gmtime(&time);
        auto tm = *std::localtime(&time);

        auto epoch = now.time_since_epoch();
        auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(epoch).count() % 1000000000;

        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y%m%d-%T.") << ns;
        return oss.str();
    }

} // namespace BeaconTech::utils
