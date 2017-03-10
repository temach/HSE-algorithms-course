cmake_minimum_required(VERSION 3.0)

project(bidilist CXX)
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

# to enable c++11 (nullptr and so on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../bin)

add_executable(bidilist
../../src/main.cpp
../../src/BidiLinkedList.h
../../src/BidiLinkedList.hpp
../../src/demos.hpp
)
set_target_properties(bidilist PROPERTIES LINKER_LANGUAGE CXX)

set(gtest_LIB "gtest")
set(gtest_main_LIB "gtest_main")
set(gtest_INCLUDE_DIR "/usr/local/include/gtest")
set(project_INCLUDE_DIR "/home/artem/Desktop/Uni/algo-structs/17-hw-bidi-linkedlist/src")
include_directories(${project_INCLUDE_DIR})
include_directories(${gtest_INCLUDE_DIR})

add_executable(bidilist_test
../../src/BidiLinkedList.h
../../tests/gtest/BidiLinkedList_Test.cpp
)
target_link_libraries(bidilist_test ${gtest_LIB} ${gtest_main_LIB})
set_target_properties(bidilist_test PROPERTIES LINKER_LANGUAGE CXX)

