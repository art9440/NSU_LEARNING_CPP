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

    std::vector<WavFile> inputWavs;
    for (const std::string& inputFile : parser.get_input_files()) {
        WavFile inputWav;
        if (!inputWav.read(inputFile)) {
            std::cerr << "Can`t read file: " << inputFile << std::endl;
            return 1;
        }
        inputWavs.push_back(std::move(inputWav));
    }

    std::vector<int16_t> samples = inputWavs[0].getSamples();


    std::vector<Converter*> converters;



}
