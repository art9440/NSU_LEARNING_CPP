cmake_minimum_required(VERSION 3.8)

project(LifeGame_lab2)

# Подключаем Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# Для Windows: предотвращаем переопределение настроек компилятора/ссылок
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Создаем основное исполняемое приложение
add_executable(LifeGame_lab2 
  LifeGame_lab2.cpp 
  ParseConsole.cpp 
  Universe.cpp 
  Cell.cpp
)

# Создаем библиотеку для кода игры, чтобы можно было переиспользовать в тестах
add_library(LifeGameLib
  ParseConsole.cpp 
  Universe.cpp 
  Cell.cpp
)

# Включаем тестирование
enable_testing()

# Создаем исполняемый файл для тестов
add_executable(hello_test tests.cc)

# Подключаем Google Test и библиотеку LifeGameLib к тестам
target_link_libraries(
  hello_test
  GTest::gtest_main
  LifeGameLib
)

# Включаем автоматическое обнаружение тестов
include(GoogleTest)
gtest_discover_tests(hello_test)
