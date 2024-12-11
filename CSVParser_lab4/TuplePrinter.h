#pragma once

#include <tuple>

#include <iostream>
#include <string>



template<typename Ch, typename Tr, typename Tuple, size_t N>
class TuplePrinter {
public:
	static void print(std::basic_ostream<Ch, Tr>& outputStream, const Tuple& tuple) {
		TuplePrinter<Ch, Tr, Tuple, N - 1>::print(outputStream, tuple);
		outputStream << "; " << std::get<N - 1>(tuple);
	}
};

template<typename Ch, typename Tr, typename Tuple>
class TuplePrinter<Ch, Tr, Tuple, 1> {
public:
	static void print(std::basic_ostream<Ch, Tr>& outputStream, const Tuple& tuple) {
		outputStream << std::get<0>(tuple);
	}
};

template<typename Ch, typename Tr, typename... Args>
std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& outputStream, const std::tuple<Args...>& tuple) {
	outputStream << "{ ";
	TuplePrinter<Ch, Tr, decltype(tuple), sizeof...(Args)>::print(outputStream, tuple);
	outputStream << " }";
	return outputStream;
}