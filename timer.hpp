#ifndef TIMER_HPP
#define TIMER_HPP
#include <string>
#include <chrono>
#include <iostream>
class Timer{
  std::chrono::high_resolution_clock::time_point t1, t2;
public:
  Timer(){
    t1 = std::chrono::high_resolution_clock::now();
  }
  void reset(){
    t1 = std::chrono::high_resolution_clock::now();
  }
  void end(std::string log = "Timer Take"){
    t2 = std::chrono::high_resolution_clock::now();
    auto total = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout << log << " : " << total.count() << " milliseconds.\n";
  }
};

#endif//TIMER_HPP
