# CMakeList.txt: проект CMake для CSVParser_lab4; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.


project ("CSVParser_lab4")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (CSVParser_lab4 "CSVParser_lab4.cpp"  "CSVParser.h" "TupleReader.h" "Exceptions.h" 
"TuplePrinter.h" )

add_library(CSVLib
  "CSVParser_lab4.cpp"  "CSVParser.h" "TupleReader.h" "Exceptions.h" 
"TuplePrinter.h"
)

enable_testing()

add_executable(hello_test tests.cc)

target_link_libraries(
  hello_test
  GTest::gtest_main
  CSVLib
)

include(GoogleTest)
gtest_discover_tests(hello_test)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
