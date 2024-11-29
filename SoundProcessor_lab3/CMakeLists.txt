# CMakeList.txt: проект CMake для SoundProcessor_lab3; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SoundProcessor_lab3")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)



# Добавьте источник в исполняемый файл этого проекта.
add_executable (SoundProcessor_lab3 "SoundProcessor_lab3.cpp"  "WavFile.cpp" "WavFile.h" 
"Converter.cpp" "Converter.h" "ParseConsole.cpp" "ParseConsole.h" "ParseConfig.cpp" "ParseConfig.h" "ConverterFactory.cpp" "ConverterFactory.h" "Exceptions.cpp")


add_library(SoundProcessorLib
  ParseConsole.cpp 
  SoundProcessor_lab3.cpp WavFile.cpp Converter.cpp ParseConfig.cpp 
  ConverterFactory.cpp Exceptions.cpp
)

enable_testing()

add_executable(hello_test tests.cc)

target_link_libraries(
  hello_test
  GTest::gtest_main
  SoundProcessorLib
)

include(GoogleTest)
gtest_discover_tests(hello_test)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SoundProcessor_lab3 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
