cmake_minimum_required(VERSION 3.14)

find_package(GTest REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(OScolloc_1_tests
    test_main.cpp
    test_fibonacci.cpp
    test_palindrome.cpp
    test_linklist.cpp
    ${CMAKE_SOURCE_DIR}/src/fibonacci.cpp
    ${CMAKE_SOURCE_DIR}/src/palindrome.cpp
)

target_link_libraries(OScolloc_1_tests
    GTest::gtest
    GTest::gtest_main
)

add_test(NAME OScolloc_1_tests COMMAND OScolloc_1_tests)