#include <iostream>
#include "WavFile.h"
#include "ParseConsole.h"
#include "ParseConfig.h"
#include "ConverterFactory.h"
#include "Exceptions.h"



int main(int argc, char *argv[])
{
	ParseConsole parser;
    try {
        if (!parser.parsing(argc, argv)) {
            if (parser.use_help()) {
                return 0;
            }
            else {
                throw std::runtime_error("Failed to parse command line arguments.");
                return 1;
            }
        }
    }
    catch (const ParseConsoleException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "config_file:" << parser.get_config_file() << "\n";
    std::cout << "output_file:" << parser.get_output_file() << "\n";
    std::cout << "input_files:" << std::endl;
    parser.Show_input_files(parser.get_input_files());


    std::vector<WavFile> inputWavs;
    for (const std::string& inputFile : parser.get_input_files()) {
        WavFile inputWav;
        try {
            inputWav.read(inputFile);
            
            inputWavs.push_back(std::move(inputWav));
        }
        catch (const WavFileException& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    }

    if (inputWavs.empty()) {
        std::cerr << "No input files." << std::endl;
        return 1;
    }

    ParseConfig configParser;
    std::vector<std::string> configLines;
    try {
        configParser.readConfigFile(parser.get_config_file(), configLines);
    }
    catch (const ConfigFileOpenException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::vector<std::unique_ptr<Converter>> converters;
    for (const std::string& line : configLines) {
        std::cout << line << std::endl;
        try {
            std::unique_ptr<Converter> converter = ConverterFactory::createConverterFromLine(line, inputWavs);
            converters.push_back(std::move(converter));
        }
        catch (const ConverterException& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    }
    //std::cout <<"Amount of converters:" << sizeof(converters) << std::endl;

    std::vector<int16_t> samples = inputWavs[0].getSamples();
    //std::cout <<"RAte: " << inputWavs[0].getSampleRate() << std::endl;
    for (auto& converter : converters) {
        samples = converter->process(samples);
        //std::cout << "after converter: " << samples.size() << " samples" << std::endl;
    }

    //std::cout << "Amount of Samples: " << samples.size() << std::endl;
    WavFile outputWav;
    outputWav.getSamples() = samples; // Задаем обработанные сэмплы
    try {
        outputWav.write(parser.get_output_file());
    }
    catch (WavFileException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Processing is done." << std::endl;
    return 0;
}
