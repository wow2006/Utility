#ifndef TIMER_HPP
#define TIMER_HPP
#include <string>
#include <sstream>
#include <iostream>
#include "logger.hpp"

#if(_MSC_VER == 1800)
#include <chrono>
class Timer{
	std::chrono::high_resolution_clock::time_point t1, t2;
	LoggerSystem* mLogger;
public:
	Timer() : mLogger(nullptr){}
	Timer(LoggerSystem* _logger) : mLogger(_logger){}
	void start(){
		t1 = std::chrono::high_resolution_clock::now();
	}
	void reset(){
		t1 = std::chrono::high_resolution_clock::now();
	}
	void end(std::ostream _output, std::string log = "Timer Take"){
		t2 = std::chrono::high_resolution_clock::now();
		auto total = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
		_output << log << " : " << total.count() << " milliseconds.\n";
	}
	void end(std::string log = "Timer Take"){
		if (mLogger == nullptr)
			return;
		t2 = std::chrono::high_resolution_clock::now();
		auto total = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
		std::stringstream buffer;
		buffer << log << " : " << total.count() << " milliseconds.\n";
		(*mLogger) << buffer.str();
	}
};
#else
#include <boost\chrono.hpp>
class Timer{
	boost::chrono::high_resolution_clock::time_point t1, t2;
	LoggerSystem* mLogger;
public:
	Timer() : mLogger(nullptr){}
	Timer(LoggerSystem* _logger) : mLogger(_logger){
	}
	void start(){
		t1 = boost::chrono::high_resolution_clock::now();
	}
	void reset(){
		t1 = boost::chrono::high_resolution_clock::now();
	}
	void end(std::ostream _output, std::string log = "Timer Take"){
		t2 = boost::chrono::high_resolution_clock::now();
		auto total = boost::chrono::duration_cast<boost::chrono::milliseconds>(t2 - t1);
		_output << log << " : " << total.count() << " milliseconds.\n";
	}
	void end(std::string log = "Timer Take"){
		if (mLogger == nullptr)
			return;
		t2 = boost::chrono::high_resolution_clock::now();
		auto total = boost::chrono::duration_cast<boost::chrono::milliseconds>(t2 - t1);
		std::stringstream buffer;
		buffer << log << " : " << total.count() << " milliseconds.\n";
		(*mLogger) << buffer.str();
	}
};
#endif

#endif//TIMER_HPP
