cmake_minimum_required(VERSION 3.0)

project(safe-array CXX)
set(CMAKE_BUILD_TYPE Debug)

# to enable c++11 (nullptr and so on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(INTERMEDIATE_DIR ${CMAKE_CURRENT_BINARY_DIR}/tmpfiles)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../src ${INTERMEDIATE_DIR}/sol)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../tests ${INTERMEDIATE_DIR}/tests)
