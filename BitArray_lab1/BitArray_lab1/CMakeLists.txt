
add_executable (BitArray_lab1 "BitArray_lab1.cpp" "BitArray_lab1.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BitArray_lab1 PROPERTY CXX_STANDARD 20)
endif()


