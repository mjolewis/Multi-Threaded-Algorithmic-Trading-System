//
// A simple utility class to measure elapsed time. Typical use cases are for profiling the
// running time of algorithms.
//
// Created by Michael Lewis on 7/6/23.
//

#include "StopWatch.hpp"

namespace BeaconTech::Common
{

    void StopWatch::start()
    {
        startTime = std::chrono::steady_clock::now();
    }

    void StopWatch::stop()
    {
        stopTime = std::chrono::steady_clock::now();
    }

    void StopWatch::reset()
    {
        stopTime = startTime = std::chrono::steady_clock::now();
    }

    //Calculates the difference between the stop time and start time
    double StopWatch::elapsedTime() const
    {
        auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);

        return std::chrono::duration<double>(elapsedTime).count();
    }
} // namespace BeaconTech::Utils
