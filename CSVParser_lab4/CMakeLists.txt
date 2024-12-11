# CMakeList.txt: проект CMake для CSVParser_lab4; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.


project ("CSVParser_lab4")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (CSVParser_lab4 "CSVParser_lab4.cpp"  "CSVParser.h" "TupleReader.h" "Exceptions.h" 
"TuplePrinter.h" )



# TODO: Добавьте тесты и целевые объекты, если это необходимо.
