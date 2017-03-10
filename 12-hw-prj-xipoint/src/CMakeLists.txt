cmake_minimum_required (VERSION 3.2)
project (xipoint_main)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -g")
set(CMAKE_BUILD_TYPE "Debug")
add_executable(xipoint_main 
    main.cpp
    xipoint.cpp
    xipoint.h
)

