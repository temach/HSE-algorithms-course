cmake_minimum_required(VERSION 3.0)

project(Point CXX)
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

#set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)

# toolchain options


#set(CMAKE_SYSTEM_NAME "Windows")                            # OS Name
#set(CMAKE_MAKE_PROGRAM "c:/programs/MinGW/bin/mingw32-make.exe")      # compiler file name. In this case, cross-compiler
#set(CMAKE_C_COMPILER "c:/programs/MinGW/bin/gcc.exe")      # compiler file name. In this case, cross-compiler
#set(CMAKE_CXX_COMPILER "c:/programs/MinGW/bin/g++.exe")
#set(CMAKE_SYSTEM_PROCESSOR "i686")                      #processor name

# to enable c++11 (nullptr and so on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


#if native compiler is used, the lines below should be removed

#These variables only matter if cross-compiling
# target environment root
#set(CMAKE_FIND_ROOT_PATH "/usr/i686-w64-mingw32")


# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search
# programs in the host environment
#set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
#set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)



set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(INTERMEDIATE_DIR ${CMAKE_CURRENT_BINARY_DIR}/intermediate)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../src ${INTERMEDIATE_DIR}/sol)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../tests ${INTERMEDIATE_DIR}/tests)
