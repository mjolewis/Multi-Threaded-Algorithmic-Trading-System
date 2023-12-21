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
#include <string>
#include <sstream>

#include "Logger.hpp"
#include "CommonServer/logging/LogLevel.hpp"
#include "CommonServer/logging/LogElement.hpp"
#include "CommonServer/utils/Clock.hpp"

namespace BeaconTech::Common
{
    Logger::Logger(const std::string& appName)
        : fileName{"./" + appName + "/logs/" + appName + ".log"}, clfq{}, running{true}, loggerThread()
    {
        while (!file.is_open())
        {
            std::filesystem::create_directories("./" + appName + "/logs/");
            file.open(this->fileName, std::ios_base::out);
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
    void Logger::pushValue(const BeaconTech::Common::LogElement &logElement) noexcept
    {
        *(clfq.getNextToWriteTo()) = logElement;
        clfq.updateWriteIndex();
    }

    // Creates a LogElement and passes it to the function that actually writes to the CLFQ
    void Logger::pushValue(const char value) noexcept
    {
        pushValue(LogElement{LogType::CHAR, { .c = value }});
    }

    // Accepts a collection of characters (e.g. char*) and pushes each char into the CLFQ one at a time
    // todo - Upgrade to use memcpy while handling the wrapping of indices at the end of the queue
    void Logger::pushValue(const char* value) noexcept
    {
        while (*value)
        {
            pushValue(*value);
            ++value;
        }
    }

    // Converts a string into a pointer to an array of characters and push each char into the CLFQ one at a time
    void Logger::pushValue(const std::string& value) noexcept
    {
        pushValue(value.c_str());
    }

    void Logger::pushValue(const int value) noexcept
    {
        pushValue(LogElement{LogType::INTEGER, { .i = value }});
    }

    void Logger::pushValue(const long value) noexcept
    {
        pushValue(LogElement{LogType::LONG_INTEGER, { .l = value }});
    }

    void Logger::pushValue(const long long value) noexcept
    {
        pushValue(LogElement{LogType::LONG_LONG_INTEGER, { .ll = value }});
    }

    void Logger::pushValue(const unsigned value) noexcept
    {
        pushValue(LogElement{LogType::UNSIGNED_INTEGER, { .u = value }});
    }

    void Logger::pushValue(const unsigned long value) noexcept
    {
        pushValue(LogElement{LogType::UNSIGNED_LONG_INTEGER, { .ul = value }});
    }

    void Logger::pushValue(const unsigned long long value) noexcept
    {
        pushValue(LogElement{LogType::UNSIGNED_LONG_LONG_INTEGER, { .ull = value }});
    }

    void Logger::pushValue(const float value) noexcept
    {
        pushValue(LogElement{LogType::FLOAT, { .f = value }});
    }

    void Logger::pushValue(const double value) noexcept
    {
        pushValue(LogElement{LogType::DOUBLE, { .d = value }});
    }

    // Logs an info message to disk
    void Logger::logInfo(const std::string &clazz, const std::string &method, const char *s) noexcept
    {
        std::string dateAndTime = BeaconTech::Common::Clock::getLocalDateAndTime();
        std::string msg = dateAndTime + " " + LogLevel::INFO.getDesc() + "  " + clazz + " " + method + ": " + s;

        log(msg.c_str());
    }

    // Logs a warning message to disk
    void Logger::logWarn(const std::string &clazz, const std::string &method, const char *s) noexcept
    {
        std::string dateAndTime = BeaconTech::Common::Clock::getLocalDateAndTime();
        std::string msg = dateAndTime + " " + LogLevel::WARN.getDesc() + "  " + clazz + " " + method + ": " + s;

        log(msg.c_str());
    }

    // Logs an error message to disk
    void Logger::logSevere(const std::string &clazz, const std::string &method, const char *s) noexcept
    {
        std::string dateAndTime = BeaconTech::Common::Clock::getLocalDateAndTime();
        std::string msg = dateAndTime + " " + LogLevel::SEVERE.getDesc() + "  " + clazz + " " + method + ": " + s;

        log(msg.c_str());
    }

    // Formats the log string with no arguments and pushes those characters into the CLFQ
    void Logger::log(const char* s) noexcept
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