cmake_minimum_required(VERSION 3.8)

project(LifeGame_lab2)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(LifeGame_lab2 
  LifeGame_lab2.cpp 
  ParseConsole.cpp 
  Universe.cpp 
  Cell.cpp
)

add_library(LifeGameLib
  ParseConsole.cpp 
  Universe.cpp 
  Cell.cpp
)

enable_testing()

add_executable(hello_test tests.cc)

target_link_libraries(
  hello_test
  GTest::gtest_main
  LifeGameLib
)

include(GoogleTest)
gtest_discover_tests(hello_test)
