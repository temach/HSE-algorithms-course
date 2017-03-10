cmake_minimum_required (VERSION 3.2)
project (stack-machine-test CXX)
add_executable (stack_machine_test
    # int_stack_test.cpp
    stack_machine_test.cpp
    # main.cpp
    int_stack.cpp
    int_stack.h
    stack_machine.cpp
    stack_machine.h
)
target_link_libraries(stack_machine_test gtest gtest_main)

