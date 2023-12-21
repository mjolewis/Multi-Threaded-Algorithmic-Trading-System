//
// A high-performance logging utility that formats and writes to disk using a dedicated thread.
// The system can enqueue log elements into a lock-free queue from the performance critical
// thread and allow those elements to be formatted and written to disk on a dedicated,
// non-performance critical thread.
//
// Created by Michael Lewis on 12/18/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_LOGGER_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_LOGGER_HPP

#include <atomic>
#include <fstream>
#include <string>
#include <thread>

#include "CommonServer/datastructures/ConcurrentLockFreeQueue.hpp"
#include "CommonServer/logging/LogLevel.hpp"
#include "CommonServer/logging/LogElement.hpp"
#include "CommonServer/utils/Clock.hpp"

namespace BeaconTech::Common
{

    class Logger final
    {
    private:
        // Log file info
        const std::string fileName;
        std::ofstream file;

        // A lock-free queue that holds elements from the performance critical thread.
        // The elements are formatted and written to disk by a non-performance critical thread
        Common::ConcurrentLockFreeQueue<Common::LogElement> clfq;
        std::atomic<bool> running;

        // A non-performance critical thread that writes messages to disk
        std::thread loggerThread;

        void log(const char* s) noexcept;

        // Overloaded functions to write different log entry types to the lock free queue.
        // Creates a LogElement of the correct type and writes it to the lock free queue.
        void pushValue(const LogElement& logElement) noexcept;

        void pushValue(char value) noexcept;

        void pushValue(const char* value) noexcept;

        void pushValue(const std::string& value) noexcept;

        void pushValue(int value) noexcept;

        void pushValue(long value) noexcept;

        void pushValue(long long value) noexcept;

        void pushValue(unsigned value) noexcept;

        void pushValue(unsigned long value) noexcept;

        void pushValue(unsigned long long value) noexcept;

        void pushValue(float value) noexcept;

        void pushValue(double value) noexcept;

    public:
        explicit Logger(const std::string& appName);

        virtual ~Logger();

        void flushQueue() noexcept;

        // Overloaded functions that handles log elements with no substituted arguments
        void logInfo(const std::string& className, const std::string& funcName, const char* s) noexcept;

        void logWarn(const std::string& className, const std::string& funcName, const char* s) noexcept;

        void logSevere(const std::string& className, const std::string& funcName, const char* s) noexcept;

        // Overloaded functions that allows clients to specify the log level and the content to log
        // Logs an info message to disk
        template<typename T, typename... Args>
        void logInfo(const std::string& className, const std::string& funcName,
                             const char* s, const T& value, Args... args) noexcept
        {
            std::string dateAndTime = BeaconTech::Common::Clock::getLocalDateAndTime();
            std::string msg = dateAndTime + " " + LogLevel::INFO.getDesc() + "  " + className + " " + funcName + ": " + s;

            log(msg.c_str(), value, args...);
        }

        // Logs a warning message to disk
        template<typename T, typename... Args>
        void logWarn(const std::string &className, const std::string &funcName,
                             const char *s, const T &value, Args ...args) noexcept
        {
            std::string dateAndTime = BeaconTech::Common::Clock::getLocalDateAndTime();
            std::string msg = dateAndTime + " " + LogLevel::WARN.getDesc() + "  " + className + " " + funcName + ": " + s;

            log(msg.c_str(), value, args...);
        }

        // Logs an error message to disk
        template<typename T, typename...Args>
        void logSevere(const std::string &className, const std::string &funcName,
                               const char *s, const T &value, Args ...args) noexcept
        {
            std::string dateAndTime = BeaconTech::Common::Clock::getLocalDateAndTime();
            std::string msg = dateAndTime + " " + LogLevel::SEVERE.getDesc() + "  " + className + " " + funcName + ": " + s;
            log(msg.c_str(), value, args...);
        }

        // Formats the log string by substituting the % character with the values to be logged
        // and pushes those characters into the CLFQ
        template<typename T, typename... Args>
        void log(const char* s, const T& value, Args... args) noexcept
        {
            while (*s)
            {
                if (*s == '%')
                {
                    // Allow %% -> % escape character
                    if (*(s + 1) == '%') [[unlikely]]
                    {
                        ++s;
                    }
                    else
                    {
                        pushValue(value);
                        log(s + 1, args...);
                        return;
                    }
                }

                pushValue(*s++);
            }

            pushValue("\n");
        }

        // Deleted default ctors and assignment operators
        Logger() = delete;

        Logger(const Logger& other) = delete;

        Logger(Logger&& other) = delete;

        Logger& operator=(const Logger& other) = delete;

        Logger& operator=(Logger&& other) = delete;
    };

} // BeaconTech::Common

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_LOGGER_HPP
