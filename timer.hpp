#ifndef TIMER_HPP
#define TIMER_HPP
#include "logger.hpp"

#if !defined(USE_CXX98)
#include <chrono>
using namespace std::chrono;
#elif defined(USE_BOOST)
#include <boost\chrono.hpp>
using namespace boost::chrono;
#else
#error("Can not use logger")
#endif

class Timer
{
    high_resolution_clock::time_point t1, t2;
    LoggerSystem* mLogger;

public:
    Timer() : mLogger(nullptr) {}

    Timer(LoggerSystem* _logger) : mLogger(_logger) {}

    void start() { t1 = high_resolution_clock::now(); }

    void reset() { t1 = high_resolution_clock::now(); }

    void end(std::ostream _output, std::string log = "Timer Take") {
        t2 = high_resolution_clock::now();
        auto total = duration_cast<milliseconds>(t2 - t1);
        _output << log << " : " << total.count() << " milliseconds.\n";
    }

    void end(std::string log = "Timer Take") {
        if (mLogger == nullptr) return;
        t2 = high_resolution_clock::now();
        auto total = duration_cast<milliseconds>(t2 - t1);
        std::stringstream buffer;
        buffer << log << " : " << total.count() << " milliseconds.\n";
        (*mLogger) << buffer.str();
    }
};

#endif  // TIMER_HPP
