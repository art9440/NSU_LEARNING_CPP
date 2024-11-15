#include <iostream>
#include "WavFile.h"
#include "ParseConsole.h"
#include "Converter.h"


int main(int argc, char *argv[])
{
	ParseConsole parser;

    if (!parser.parsing(argc, argv)) {
        if (parser.use_help()) {
            return 0;
        }
        else {
            std::cerr << "Error: Failed to parse command line arguments." << std::endl;
            return 1;
        }
    }

    std::cout << "config_file:" << parser.get_config_file() << "\n";
    std::cout << "output_file:" << parser.get_output_file() << "\n";
    std::cout << "input_files:" << std::endl;
    parser.Show_input_files(parser.get_input_files());
}
