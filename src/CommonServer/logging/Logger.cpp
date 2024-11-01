//
// A high-performance logging utility that formats and writes to disk using a dedicated thread.
// The system can enqueue log elements into a lock-free queue from the performance critical
// thread and allow those elements to be formatted and written to disk on a dedicated,
// non-performance critical thread.
//
// Created by Michael Lewis on 12/18/23.
//

#include <filesystem>
#include <iostream>
#include <mutex>
#include <string>
#include <sstream>

#include "Logger.hpp"
#include "CommonServer/logging/LogLevel.hpp"
#include "CommonServer/logging/LogElement.hpp"
#include "CommonServer/utils/Clock.hpp"

namespace BeaconTech::Common
{
    Logger::Logger(const std::string& filePath, const std::string& appName, uint32_t engineId)
        : directory{filePath + "/logs/"}, fileName{filePath + "/logs/" + appName + ".log"},
          file{fileName, std::ios::app}, clfq{}, running{true}, engineId{engineId}, loggerThread()
    {
        if (!std::filesystem::exists(fileName))
        {
            std::filesystem::create_directories(directory);
        }

        if (!file.is_open())
        {
            // opened in append mode
            file.open(this->fileName, std::ios_base::app);
        }

        loggerThread = std::thread([this]() { flushQueue(); } );

//        if (loggerThread == nullptr)
//        {
//            std::cerr << Common::LogLevel::SEVERE.getDesc()
//                      << ": Failed to start logging thread for" << fileName << std::endl;
//        }
    }

    Logger::~Logger()
    {
        while (!clfq.size())
        {
            // noop - continue draining the queue
        }

        running = false;
        if (loggerThread.joinable())
        {
            loggerThread.join();
            file.close();
        }
    }

    // Consumes log entries from the lock free queue and writes them to the log file
    void Logger::flushQueue() noexcept
    {
        while (running)
        {
            for (auto next = clfq.getNextToRead(); clfq.size() && next; next = clfq.getNextToRead())
            {
                switch (next->logType)
                {
                    case LogType::CHAR:
                        file << next->u.c;
                        break;
                    case LogType::INTEGER:
                        file << next->u.i;
                        break;
                    case LogType::LONG_INTEGER:
                        file << next->u.l;
                        break;
                    case LogType::LONG_LONG_INTEGER:
                        file << next->u.ll;
                        break;
                    case LogType::UNSIGNED_INTEGER:
                        file << next->u.u;
                        break;
                    case LogType::UNSIGNED_LONG_INTEGER:
                        file << next->u.ul;
                        break;
                    case LogType::UNSIGNED_LONG_LONG_INTEGER:
                        file << next->u.ull;
                        break;
                    case LogType::FLOAT:
                        file << next->u.f;
                        break;
                    case LogType::DOUBLE:
                        file << next->u.d;
                        break;
                }

                clfq.updateNextToRead();
            }

            file.flush();
        }
    }

    // Writes the log element onto the lock free queue and updates its index
    void Logger::pushValue(const BeaconTech::Common::LogElement &logElement) const noexcept
    {
        *(clfq.getNextToWriteTo()) = logElement;
        clfq.updateWriteIndex();
    }

    // Creates a LogElement and passes it to the function that actually writes to the CLFQ
    void Logger::pushValue(const char value) const noexcept
    {
        pushValue(LogElement{LogType::CHAR, { .c = value }});
    }

    // Accepts a collection of characters (e.g. char*) and pushes each char into the CLFQ one at a time
    // todo - Upgrade to use memcpy while handling the wrapping of indices at the end of the queue
    void Logger::pushValue(const char* value) const noexcept
    {
        while (*value)
        {
            pushValue(*value);
            ++value;
        }
    }

    // Converts a string into a pointer to an array of characters and push each char into the CLFQ one at a time
    void Logger::pushValue(const std::string& value) const noexcept
    {
        pushValue(value.c_str());
    }

    void Logger::pushValue(const int value) const noexcept
    {
        pushValue(LogElement{LogType::INTEGER, { .i = value }});
    }

    void Logger::pushValue(const long value) const noexcept
    {
        pushValue(LogElement{LogType::LONG_INTEGER, { .l = value }});
    }

    void Logger::pushValue(const long long value) const noexcept
    {
        pushValue(LogElement{LogType::LONG_LONG_INTEGER, { .ll = value }});
    }

    void Logger::pushValue(const unsigned value) const noexcept
    {
        pushValue(LogElement{LogType::UNSIGNED_INTEGER, { .u = value }});
    }

    void Logger::pushValue(const unsigned long value) const noexcept
    {
        pushValue(LogElement{LogType::UNSIGNED_LONG_INTEGER, { .ul = value }});
    }

    void Logger::pushValue(const unsigned long long value) const noexcept
    {
        pushValue(LogElement{LogType::UNSIGNED_LONG_LONG_INTEGER, { .ull = value }});
    }

    void Logger::pushValue(const float value) const noexcept
    {
        pushValue(LogElement{LogType::FLOAT, { .f = value }});
    }

    void Logger::pushValue(const double value) const noexcept
    {
        pushValue(LogElement{LogType::DOUBLE, { .d = value }});
    }

    // Logs an info message to disk
    void Logger::logInfo(const std::string &clazz, const std::string &method, const char *s) const noexcept
    {
        createAndLogMsg(clazz, method, s, LogLevel::INFO);
    }

    // Logs a warning message to disk
    void Logger::logWarn(const std::string &clazz, const std::string &method, const char *s) const noexcept
    {
        createAndLogMsg(clazz, method, s, LogLevel::WARN);
    }

    // Logs an error message to disk
    void Logger::logSevere(const std::string &clazz, const std::string &method, const char *s) const noexcept
    {
        createAndLogMsg(clazz, method, s, LogLevel::SEVERE);
    }

    void Logger::createAndLogMsg(const std::string &clazz, const std::string &method, const char *s, const LogLevel& logLevel) const noexcept
    {
        // A blocking lock to ensure that all messages are written.
        // A non-blocking lock might cause a message to be skipped if the lock is already held.
        const std::lock_guard<std::mutex> lock{mutex};

//        std::stringstream ss;
//        ss << std::this_thread::get_id();

        std::string dateAndTime = BeaconTech::Common::Clock::getLocalDateAndTime();
        std::string msg = dateAndTime + " " + logLevel.getDesc() + "  " + clazz + " " + method
                          + " [CLFQ-" + std::to_string(engineId) + "]: " + s;

        log(msg.c_str());

        // The lock_guard is destroyed and the mutex is released at the end of the scope
    }

    // Formats the log string with no arguments and pushes those characters into the CLFQ
    void Logger::log(const char* s) const noexcept
    {
        while (*s)
        {
            if (*s == '%')
            {
                // Allow %% -> % escape character
                if (*(s + 1) == '%') [[likely]]
                {
                    ++s;
                }
                else
                {
                    std::cerr << "SEVERE Logger log: Missing arguments to log()" << std::endl;
                }
            }

            pushValue(*s++);
        }

        pushValue("\n");
    }

} // BeaconTech