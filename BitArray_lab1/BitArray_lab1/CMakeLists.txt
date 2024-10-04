cmake_minimum_required(VERSION 2.4)

project(BitArray_lab1)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(BitArray BitArray_lab1.h BitArray_lab1.cpp main.cpp)

enable_testing()

add_executable(
  tests
  tests.cc
  BitArray_lab1.cpp
 )

target_link_libraries(
  tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)