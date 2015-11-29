project(Testing)
cmake_minimum_required(VERSION 2.8)

message("Current C++ Compiler is ${CMAKE_CXX_COMPILER_ID}")
# add C++11 Support
add_definitions("-std=c++11 -Wall -g")
# Enable Debug
set(CMAKE_BUILD_TYPE Debug)

# Find Boost Library
set(Boost_USE_MULTITHREADED     ON)
find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

# Find CUDA Library
find_package(CUDA REQUIRED)
include_directories(${CUDA_INCLUDE_DIRS})

#
set(sources main.cpp timer.hpp logger.hpp xmlparser.hpp kdtree.hpp)

#
add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} -pthread ${Boost_LIBRARIES} ${CUDA_LIBRARIES})
