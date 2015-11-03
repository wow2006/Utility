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
		if(mLogger == nullptr)
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
	Timer(): mLogger(nullptr){}
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
		if(mLogger == nullptr)
			return;
		t2 = boost::chrono::high_resolution_clock::now();
		auto total = boost::chrono::duration_cast<boost::chrono::milliseconds>(t2 - t1);
		std::stringstream buffer;
		buffer << log << " : " << total.count() << " milliseconds.\n";
		(*mLogger) << buffer.str();
	}
};
#endif

#ifdef USE_CUDA
#include <cuda_runtime_api.h>
class CUDA_Timer{
	cudaEvent_t t1, t2;
	LoggerSystem* mLogger;
public:
	CUDA_Timer() : mLogger(nullptr){
		cudaEventCreate(&t1);
		cudaEventCreate(&t2);
	}
	CUDA_Timer(LoggerSystem* _logger) : mLogger(_logger){
		cudaEventCreate(&t1);
		cudaEventCreate(&t2);
	}
	~CUDA_Timer(){
		cudaEventDestroy(t1);
		cudaEventDestroy(t2);
	}
	void start(){
		cudaEventRecord(t1);
	}
	void reset(){
		cudaEventRecord(t1);
	}
	void end(std::ostream _output, std::string log = "Timer Take", cudaStream_t _stream = 0){
		cudaEventRecord(t2);
		cudaEventSynchronize(t2);
		float time = 0.0f;
		cudaEventElapsedTime(&time, t1, t2);

		cudaEventCreate(&t1);
		cudaEventRecord(t1, _stream);
		_output << log << " : " << time << " milliseconds.\n";
	}
	void end(std::string log = "Timer Take"){
		if (mLogger == nullptr)
			return;
		cudaEventRecord(t2);
		cudaEventSynchronize(t2);
		float time = 0.0f;
		cudaEventElapsedTime(&time, t1, t2);
		std::stringstream buffer;
		buffer << log << " : " << time << " milliseconds.\n";
		(*mLogger) << buffer.str();
	}
};
#endif

#endif//TIMER_HPP
