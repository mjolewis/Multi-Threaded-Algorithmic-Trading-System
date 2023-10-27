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

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CONCURRENTLOCKFREEQUEUE_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CONCURRENTLOCKFREEQUEUE_HPP

#include <atomic>
#include <functional>
#include <vector>

namespace BeaconTech::Common
{

    template<typename T>
    class ConcurrentLockFreeQueue final
    {
    private:
        std::vector<std::function<void ()>> CLFQueue;
        std::atomic<size_t> nextWriteIndex;  // Index where the next element will be written to
        std::atomic<size_t> nextReadIndex;   // Index where the next element to be read can be found
        std::atomic<size_t> numElements;

    public:
        explicit ConcurrentLockFreeQueue(unsigned int threadId);

        virtual ~ConcurrentLockFreeQueue() = default;

        auto getNextToWriteTo() noexcept;

        void updateWriteIndex() noexcept;

        auto getNextToRead() const noexcept;

        void updateNextToRead() noexcept;

        auto size() const noexcept;

        // Deleted default ctors and assignment operators
        ConcurrentLockFreeQueue() = delete;

        ConcurrentLockFreeQueue(const ConcurrentLockFreeQueue& other) = delete;

        ConcurrentLockFreeQueue(ConcurrentLockFreeQueue&& other) = delete;

        ConcurrentLockFreeQueue& operator=(const ConcurrentLockFreeQueue& other) = delete;

        ConcurrentLockFreeQueue& operator=(ConcurrentLockFreeQueue&& other) = delete;
    };

} // BeaconTech::Common


//********** Start Template Definitions **********
#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CONCURRENTLOCKFREEQUEUE_CPP
#include "ConcurrentLockFreeQueue.cpp"
#endif
//********** End Template Definitions **********

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_CONCURRENTLOCKFREEQUEUE_HPP
