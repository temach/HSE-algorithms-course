cmake_minimum_required(VERSION 3.0)

project(nice-queue CXX)
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

# to enable c++11 (nullptr and so on)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Weffc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra ")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(INTERMEDIATE_DIR ${CMAKE_CURRENT_BINARY_DIR}/intermediate)

add_executable(nice-queue
    main.cpp
    NiceQueue.h
    NiceQueue.hpp
    NiceStack.h
    NiceStack.hpp
)
