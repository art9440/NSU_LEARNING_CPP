#include <iostream>
#include "ParseConsole.h"

int main(int argc, char* argv[]) {
    ParseConsole parser;
    if (!parser.parsing(argc, argv)) {
        if (parser.use_help())
            return 0;
        else {
            std::cerr << "Error: Failed to parse command line arguments." << std::endl;
            return 0;
        }
    }
    return 0;
}
