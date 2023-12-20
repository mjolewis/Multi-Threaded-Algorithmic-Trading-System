//
// A concurrent lock free queue is a wait-free and lock-free ring buffer.
// The lock-free nature of the queue enables two thread communication from a single source
// thread (the Producer) to a single destination thread (the Consumer) without using any locks.
// Also known as a Single Producer Single Consumer packet buffer.
//
// The circular FIFO nature of the ring buffer acts as a pipeline for packets to be
// deterministically written and consumed. Consumption occurs in the engine thread.
//
// NOTE 1 - A Multiple Producer Multiple Consumer lock free queue will be released in a future version
// NOTE 2 - Ctors and assignment operators have been deleted to ensure these functions aren't
// unintentionally used by clients.
//
// Created by Michael Lewis on 10/21/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CONCURRENTLOCKFREEQUEUE_CPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CONCURRENTLOCKFREEQUEUE_CPP

#include "ConcurrentLockFreeQueue.hpp"
#include "CommonServer/utils/ConfigManager.hpp"

namespace BeaconTech::Common
{
    // Pre-allocates the size of the CLFQueue with numElements and default initializes the write and read indices
    template<typename T>
    ConcurrentLockFreeQueue<T>::ConcurrentLockFreeQueue()
        : nextWriteIndex{0}, nextReadIndex{0}, numElements{0}
    {
        size_t size = Common::ConfigManager::intConfigValueDefaultIfNull("CLFQSize", 4096);
        CLFQueue = std::vector<T>{size};
    }

    // Returns a pointer to the next element to write new data to
    template<typename T>
    auto ConcurrentLockFreeQueue<T>::getNextToWriteTo() noexcept
    {
        return &CLFQueue.at(nextWriteIndex);
    }

    // Updates the next write index
    template<typename T>
    void ConcurrentLockFreeQueue<T>::updateWriteIndex() noexcept
    {
        nextWriteIndex = (nextWriteIndex + 1) % CLFQueue.size();
        numElements++;
    }

    // Returns a pointer to the next element to be consumed or a nullPtr if there is no element available
    template<typename T>
    auto ConcurrentLockFreeQueue<T>::getNextToRead() const noexcept
    {
        return (nextReadIndex == nextWriteIndex) ? nullptr : &CLFQueue.at(nextReadIndex);
    }

    // Updates the read index to point to the next element to be consumed
    template<typename T>
    void ConcurrentLockFreeQueue<T>::updateNextToRead() noexcept
    {
        nextReadIndex = (nextReadIndex + 1) % CLFQueue.size();
        numElements--;
    }

    template<typename T>
    auto ConcurrentLockFreeQueue<T>::size() const noexcept
    {
        return numElements.load();
    }
} // BeaconTech::Common


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CONCURRENTLOCKFREEQUEUE_CPP