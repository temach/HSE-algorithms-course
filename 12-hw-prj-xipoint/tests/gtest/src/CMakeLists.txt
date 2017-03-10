add_executable(xipoint_test_start
    point_test.cpp
    point_array_test.cpp
    xipoint.cpp
    xipoint.h
)

target_link_libraries(xipoint_test_start gtest gtest_main)
