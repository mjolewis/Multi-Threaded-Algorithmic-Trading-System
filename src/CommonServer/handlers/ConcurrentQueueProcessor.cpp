//
// A concurrent queue that acts as a consuming thread for inbound messages.
// The queue subsequently ensures deterministic message processing
// for downstream engines. This concurrent queue currently uses locks; however,
// it can be upgraded to use a lock free handoff between from its upstream producer
// while adhering to its protocol of deterministic message processing
//
// Created by Michael Lewis on 10/12/23.
//

#include <iostream>
#include <exception>
#include <thread>

#include "ConcurrentQueueProcessor.hpp"

namespace BeaconTech::Common
{
    // Initializes a thread pool and starts the event loop
    ConcurrentQueueProcessor::ConcurrentQueueProcessor(const unsigned int &threadId) : shouldTerminate{false}
    {
        start();
    }

    // Stops the event loop before destroying the queue processor
    ConcurrentQueueProcessor::~ConcurrentQueueProcessor()
    {
        stop();
    }

    // Creates the queue and starts the event loop
    void ConcurrentQueueProcessor::start()
    {
        threadPool.emplace_back(&ConcurrentQueueProcessor::threadLoop, this);
    }

    // Pushes work into the queue that will be processed by engine threads
    void ConcurrentQueueProcessor::enqueue(const std::function<void ()>& job)
    {
        {
            std::unique_lock<std::mutex> lock(mutex);
            concurrentQueue.push(job);
        }

        conditionVariable.notify_one();
    }

    // Event loop to process entities enqueued by the trading system.
    void ConcurrentQueueProcessor::threadLoop()
    {
        while (true)
        {
            std::function<void ()> job;
            {
                try
                {
                    // This thread will wait for data before releasing the condition variable
                    std::unique_lock<std::mutex> lock(mutex);
                    conditionVariable.wait(lock, [this] { return !concurrentQueue.empty() || shouldTerminate; });

                    // Terminate the event loop
                    if (shouldTerminate) return;

                    job = concurrentQueue.front();
                    concurrentQueue.pop();

                    // Process job before releasing the lock.
                    // This approach ensures that events are deterministically sequenced into downstream
                    // components as these components are exposed to a single thread at a time. Results
                    // in a high performance and lock free engine model with deterministic message processing
                    job();

                    // Lock is released when the scope ends
                }
                catch (const std::exception& e)
                {
                    std::cerr << e.what() << std::endl;
                }
            }
        }
    }

    // Determines if the workers still have jobs to perform
    bool ConcurrentQueueProcessor::busy()
    {
        bool isBusy;
        {
            std::unique_lock<std::mutex> lock(mutex);
            isBusy = !concurrentQueue.empty();
        }

        return isBusy;
    }

    // Blocks the current thread (usually the main thread) until the threads finish their work
    void ConcurrentQueueProcessor::stop()
    {
        {
            std::unique_lock<std::mutex> lock(mutex);
            shouldTerminate = true;
        }
        conditionVariable.notify_all();

        for (std::thread& thread : threadPool)
        {
            if (thread.joinable()) thread.join();
        }

        threadPool.clear();
    }
} // BeachTech