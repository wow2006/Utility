project(Testing)
cmake_minimum_required(VERSION 3.0)

include(./cmake/checkCompiler.cmake)

option(Utility_TEST  "" ON)
option(Utility_CUDA  "" OFF)
option(Utility_BOOST "" OFF)

if(Utility_BOOST)
    # Find Boost Library
    set(Boost_USE_MULTITHREADED     ON)
    find_package(Boost REQUIRED COMPONENTS system)
    include_directories(${Boost_INCLUDE_DIRS})
    add_definitions(-DUSE_BOOST)
endif()

if(Utility_CUDA)
    # Find CUDA Library
    find_package(CUDA REQUIRED)
    include_directories(${CUDA_INCLUDE_DIRS})
    add_definitions(-DUSE_CUDA)
endif()

if(Utility_TEST)
    enable_testing()
    add_subdirectory(test)
endif()

set(sources
    main.cpp timer.hpp logger.hpp xmlparser.hpp kdtree.hpp)

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} -pthread ${Boost_LIBRARIES} ${CUDA_LIBRARIES})
