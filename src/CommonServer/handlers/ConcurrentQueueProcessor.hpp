//
// A concurrent queue that acts as a consuming thread for inbound messages.
// The queue subsequently ensures deterministic message processing
// for downstream engines. This concurrent queue currently uses locks; however,
// it can be upgraded to use a lock free handoff between from its upstream producer
// while adhering to its protocol of deterministic message processing
//
// Created by Michael Lewis on 10/12/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CONCURRENTQUEUEPROCESSOR_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CONCURRENTQUEUEPROCESSOR_HPP

#include <functional>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <vector>

namespace BeaconTech::Common
{

    class ConcurrentQueueProcessor final
    {
    private:
        bool shouldTerminate;
        std::mutex mutex;
        std::condition_variable conditionVariable;
        std::vector<std::thread> threadPool;
        std::queue<std::function<void ()>> concurrentQueue;

        void threadLoop();

    public:
        explicit ConcurrentQueueProcessor(const unsigned int& threadId);

        virtual ~ConcurrentQueueProcessor();

        void start();

        void enqueue(const std::function<void ()>& job);

        void stop();

        bool busy();

        // Deleted default ctors and assignment operators
        ConcurrentQueueProcessor() = delete;

        ConcurrentQueueProcessor(const ConcurrentQueueProcessor& other) = delete;

        ConcurrentQueueProcessor(ConcurrentQueueProcessor&& other) = delete;

        ConcurrentQueueProcessor& operator=(const ConcurrentQueueProcessor& other) = delete;

        ConcurrentQueueProcessor& operator=(ConcurrentQueueProcessor&& other) = delete;
    };

} // BeachTech

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CONCURRENTQUEUEPROCESSOR_HPP
