//
// The processor acts as an adapter for CLFQ Producer and Consumer threads.
// The processor creates a consumer thread and provides it with a CLFQ. The
// Producer generates and enqueues data while the consumer checks the buffer
// and consumes the data if it exists.
//
// Created by Michael Lewis on 10/21/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CLFQPROCESSOR_CPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CLFQPROCESSOR_CPP

#include <iostream>
#include <thread>
#include <vector>

#include "CLFQProcessor.hpp"

namespace BeaconTech::Common
{
    template<typename T>
    CLFQProcessor<T>::CLFQProcessor() : shouldTerminate{false}, CLFQueue{}
    {
        start();
    }

    // Creates a consumer thread, gives it the function to be run, and starts the event loop
    template<typename T>
    void CLFQProcessor<T>::start()
    {
        threadPool.emplace_back(&CLFQProcessor::threadLoop, this);
    }

    // Pushes work into the queue that will be processed by engine threads
    template<typename T>
    void CLFQProcessor<T>::enqueue(const std::function<void ()>& job)
    {
        *(CLFQueue.getNextToWriteTo()) = job;
        CLFQueue.updateWriteIndex();
    }

    // Event loop to process entities enqueued by the trading system
    template<typename T>
    void CLFQProcessor<T>::threadLoop()
    {
        while (true)
        {
            try
            {
                // Terminate the event loop
                if (shouldTerminate) break;

                // Gets a pointer to the next element to be consumed or a nullPtr
                const auto job = CLFQueue.getNextToRead();
                if (job != nullptr)
                {
                    CLFQueue.updateNextToRead();  // Update the read index to point to the next element to be consumed
                    job->operator()();  // Process the job
                }
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
    }

    // Determines if the worker still has jobs to perform
    template<typename T>
    bool CLFQProcessor<T>::busy()
    {
        return CLFQueue.size() > 0;
    }

    // Blocks the current thread (usually the main thread) until the thread finish working
    template<typename T>
    void CLFQProcessor<T>::stop()
    {
        shouldTerminate = true;
        for (std::thread& thread : threadPool)
        {
            if (thread.joinable()) thread.join();
        }

        threadPool.clear();
    }
} // BeaconTech::Common


#endif