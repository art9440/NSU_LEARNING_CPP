#pragma once

#include <tuple>
#include <istream>
#include "Exceptions.h"

template<typename Ch, typename Tr, typename Head, typename... Tail>
class TupleReader {
public:
    static std::tuple<Head, Tail...> read(std::basic_istream<Ch, Tr>& inputStream, size_t lineNumber, size_t columnNumber = 1) {
        if (inputStream.eof()) {
            throw NotEnoughData(lineNumber);  // Исключение при недостаточности данных
        }

        Head data;
        inputStream >> data;

        // Проверка fail() после попытки чтения
        if (inputStream.fail() || !inputStream) {
            throw FailedToReadData(lineNumber, columnNumber);
        }

        // Рекурсивное чтение остальных данных в кортеже
        return std::tuple_cat(std::make_tuple(data), TupleReader<Ch, Tr, Tail...>::read(inputStream, lineNumber, columnNumber + 1));
    }
};

// Специализация для одного элемента в кортеже
template<typename Ch, typename Tr, typename Head>
class TupleReader<Ch, Tr, Head> {
public:
    static std::tuple<Head> read(std::basic_istream<Ch, Tr>& inputStream, size_t lineNumber, size_t columnNumber = 1) {
        if (inputStream.eof()) {
            throw NotEnoughData(lineNumber);  // Исключение при недостаточности данных
        }

        Head data;
        inputStream >> data;

        // Проверка fail() после попытки чтения
        if (inputStream.fail() || !inputStream) {
            throw FailedToReadData(lineNumber, columnNumber);
        }

        return std::make_tuple(data);  // Возвращаем кортеж с одним элементом
    }
};
