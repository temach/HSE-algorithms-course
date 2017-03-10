set(gtest_LIB "gtest")
set(gtest_main_LIB "gtest_main")

#This specifies include directory
set(gtest_INCLUDE_DIR "/usr/local/include/gtest")
set(project_INCLUDE_DIR "/home/artem/Desktop/Uni/algo-structs/15-hw-dnk-list/src")

include_directories(${CMAKE_SOURCE_DIR}/../../src) #for the main test project
include_directories(${gtest_INCLUDE_DIR})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../src ${CMAKE_CURRENT_BINARY_DIR}/src)

