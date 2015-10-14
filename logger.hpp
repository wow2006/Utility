#ifndef LOGGER
#define LOGGER
#include <iostream>   // std::cout
#include <string>     // std::string
#include <cstring>    // memchr, strlen
#include <sstream>    // std::stringstream
#include <fstream>    // std::ostream
#include <mutex>      // std::mutex, std::lock_guard
#include <thread>     // std::thread::id
#include <map>        // std::map

class LoggerSystem
{
public:
  enum class Type{
    Console,
    File,
    GUI,
    ConsoleAndFile
  };
protected:
  std::map<std::thread::id, std::stringstream> mBuffer;
  Type mType = Type::Console;
  std::ofstream mFile;
  std::mutex mMutex;
public:
  LoggerSystem(Type _type = Type::Console)
    : mType(_type){}
  LoggerSystem(const std::string& _fileName, Type _type = Type::File)
    : mType(_type){
    if(!_fileName.empty()){
        mFile.open(_fileName);
        if(!mFile.is_open()){
            mType = Type::Console;
        }
    }
  }
  ~LoggerSystem(){
    if(mFile.is_open()){
        mFile.close();
    }
  }

  LoggerSystem& operator <<(const std::string& _input){
    std::lock_guard<std::mutex> block_threads_until_finish_this_job(mMutex);
    std::thread::id id = std::this_thread::get_id();
    std::stringstream& buf = mBuffer[id];
    buf << _input;
    if(_input.find('\n') != std::string::npos)
      flush(buf);
    return *this;
  }

  LoggerSystem& operator <<(const char* _input){
    std::lock_guard<std::mutex> block_threads_until_finish_this_job(mMutex);
    std::thread::id id = std::this_thread::get_id();
    std::stringstream& buf = mBuffer[id];
    buf << _input;
    if(memchr(_input, '\n', strlen(_input)))
      flush(buf);
    return *this;
  }

  template<typename T>
  LoggerSystem& operator <<(const T& _input){
    std::lock_guard<std::mutex> block_threads_until_finish_this_job(mMutex);
    std::thread::id id = std::this_thread::get_id();
    std::stringstream& buf = mBuffer[id];
    buf << _input;
    return *this;
  }
protected:
  void flush(std::stringstream& _buffer){
    switch(mType){
      case Type::ConsoleAndFile:
        mFile << _buffer.str();
      case Type::Console:
        std::cout << _buffer.str();
        break;
      case Type::File:
        mFile << _buffer.str();
        break;
      case Type::GUI:
        break;
      }
    // Clear stringStream
    _buffer.str(std::string());
  }
};
#endif // LOGGER
