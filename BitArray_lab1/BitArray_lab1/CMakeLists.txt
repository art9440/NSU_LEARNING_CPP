﻿cmake_minimum_required (VERSION 3.8)

project ("lab1")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable (lab1 "main.cpp"  "BitArray_lab1.cpp" "BitArray_lab1.h" )

enable_testing()

add_executable(
  hello_test
  tests.cc
  BitArray_lab1.cpp
 )

target_link_libraries(
  hello_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)

