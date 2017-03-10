# to enable c++11 (nullptr and so on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${gtest_INCLUDE_DIR})
include_directories(${project_INCLUDE_DIR})

add_executable(broken_dna_test
    linkedlist_test.cpp
    dna_repairer_test.cpp
    # ${CMAKE_SOURCE_DIR}../../../../src/dna_element.h
    # ${CMAKE_SOURCE_DIR}../../../../src/dna_repairer.h
    # ${CMAKE_SOURCE_DIR}../../../../src/linked_list.h
)
message(STATUS "hello people !!! WWWW WWWWW WWWW ${CMAKE_SOURCE_DIR}")
message(STATUS "Another people !!! yyyyyyyyyyyyyyy ${project_INCLUDE_DIR}")

target_link_libraries(broken_dna_test ${gtest_LIB} ${gtest_main_LIB})
