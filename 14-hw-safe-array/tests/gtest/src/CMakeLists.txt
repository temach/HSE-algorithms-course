cmake_minimum_required(VERSION 3.0)

set(gtest_LIB "gtest")
set(gtest_main_LIB "gtest_main")

#This specifies include directory
set(gtest_INCLUDE_DIR "/usr/local/include/gtest")

set(CMAKE_BUILD_TYPE Debug)

# to enable c++11 (nullptr and so on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${gtest_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/../../../src)

add_executable(safe_array_test_start 
    safearray_test.cpp
    subject_test.cpp
    ${CMAKE_SOURCE_DIR}/../../../src/safearray.h
    ${CMAKE_SOURCE_DIR}/../../../src/safearray.hpp
    ${CMAKE_SOURCE_DIR}/../../../src/subject.h
    ${CMAKE_SOURCE_DIR}/../../../src/subject.cpp
)
message(STATUS "hello people !!! WWWW WWWWW WWWW ${CMAKE_SOURCE_DIR}")

target_link_libraries(safe_array_test_start ${gtest_LIB} ${gtest_main_LIB})
