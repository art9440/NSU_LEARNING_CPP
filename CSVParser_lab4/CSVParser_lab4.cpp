#include <iostream>
#include <fstream>
#include "CSVParser.h"
#include "Exceptions.h"
#include "TuplePrinter.h"

int main() {
	std::ifstream file{ "C:\\Users\\user\\source\\repos\\NSU_LEARNING_CPP\\CSVPArser_lab4\\build\\Debug\\test.csv" };
	if (file.fail()) {
		std::cout << "The file could not be opened." << std::endl;
		return 0;
	}

	CSVParser<size_t, std::string, int, std::string, double> parser(file, 1);
	try {
		for (auto tuple : parser) {
			std::cout << tuple << std::endl;
		}
	}
	catch (NotEnoughData& e) {
		std::cout << e.what() << "Line: " << e.getLineNumber() << "." << std::endl;
	}
	catch (FailedToReadData& e) {
		std::cout << e.what() << "Line: " << e.getLineNumber() << ". Column: " << e.getColumnNumber() << "." << std::endl;
	}

	file.close();
	return 0;
}
