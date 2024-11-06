//
// The processor acts as an adapter for CLFQ Producer and Consumer threads.
// The processor creates a consumer thread and provides it with a CLFQ. The
// Producer generates and enqueues data while the consumer checks the buffer
// and consumes the data if it exists.
//
// Created by Michael Lewis on 10/21/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CLFQPROCESSOR_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CLFQPROCESSOR_HPP

#include <atomic>
#include <functional>
#include <memory>
#include <thread>
#include <vector>

#include "../datastructures/ConcurrentLockFreeQueue.hpp"

namespace BeaconTech::Common
{

    template<typename T>
    class CLFQProcessor
    {
    private:
        bool shouldTerminate;
        ConcurrentLockFreeQueue<T> CLFQueue;
        std::vector<std::thread> threadPool;

        void threadLoop();

    public:
        CLFQProcessor();

        virtual ~CLFQProcessor() = default;

        void start();

        void enqueue(const std::function<void ()>& job);

        void stop();

        bool busy();

        // Deleted default ctors and assignment operators
        CLFQProcessor(const CLFQProcessor& other) = delete;

        CLFQProcessor(CLFQProcessor&& other) = delete;

        CLFQProcessor& operator=(const CLFQProcessor& other) = delete;

        CLFQProcessor& operator=(CLFQProcessor&& other) = delete;
    };

} // BeaconTech::Common

//********** Start Template Definitions **********
#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CLFQPROCESSOR_CPP
#include "CLFQProcessor.cpp"
#endif

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CLFQPROCESSOR_HPP
