cmake_minimum_required(VERSION 3.0)

set(MAINNAME "spellcheck")

project(${MAINNAME} CXX)
# if (NOT CMAKE_BUILD_TYPE)
#   set(CMAKE_BUILD_TYPE Debug)
# endif(NOT CMAKE_BUILD_TYPE)

# to enable c++11 (nullptr and so on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og -g -Wall -Wextra -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)


set(gtest_LIB "gtest")
set(gtest_main_LIB "gtest_main")
set(gtest_INCLUDE_DIR "/usr/local/include/gtest")
set(project_INCLUDE_DIR "/home/artem/Desktop/Uni/algo-structs/23-hw-spellcheck/src")
include_directories(${project_INCLUDE_DIR})
include_directories(${gtest_INCLUDE_DIR})

add_executable(${MAINNAME}
../src/dictionary.cpp
../src/hashset.cpp
../src/main.cpp
../src/dictionary.h
../src/hashset.h
)

set_target_properties(${MAINNAME} PROPERTIES LINKER_LANGUAGE CXX)



# add_executable(fifo_test
# ../src/fifo.h
# ../src/event.h
# ../src/job.h
# ../src/simulator.h
# ../../tests/fifo_test.cpp
# )
# target_link_libraries(fifo_test ${gtest_LIB} ${gtest_main_LIB})
# set_target_properties(fifo_test PROPERTIES LINKER_LANGUAGE CXX)

