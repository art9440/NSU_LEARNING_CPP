#include "ParseConsole.h"
#include "Exceptions.h"
#include <iostream>
#include <vector>
#include <string>

ParseConsole::ParseConsole() : config_file("none"), output_file("none"), input_files(), use_help_(false) {}

std::vector<std::string> ParseConsole::get_input_files() const { return input_files; }
std::string ParseConsole::get_output_file() const { return output_file; }
bool ParseConsole::use_help() const { return use_help_; }
bool ParseConsole::hasConfig() const { return !config_file.empty(); }
std::string ParseConsole::get_config_file() const { return config_file; }

bool ParseConsole::parsing(int argc, char* argv[]) {
    try {
        if (argc < 5) {
            throw ParseInsufficientArgumentsException();  // Недостаточно аргументов
        }

        int index = 1;
        if (std::string(argv[index]) == "-c") {
            if (index + 1 < argc) {
                config_file = argv[++index];
            }
            else {
                throw InvalidConfigFileException();  // Нет конфигурационного файла
            }
            index++;
        }
        else if (std::string(argv[index]) == "-h") {
            use_help_ = true;
            help_me();
            return false;
        }
        else {
            throw MissingFlagException();  // Нет флага -c
        }

        if (index < argc) {
            output_file = argv[index++];
        }
        else {
            throw MissingOutputFileException();  // Нет выходного файла
        }

        while (index < argc) {
            input_files.push_back(argv[index++]);
        }

        if (input_files.empty()) {
            throw MissingInputFilesException();  // Нет входных файлов
        }

        return true;
    }
    catch (const ParseConsoleException& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

void ParseConsole::help_me() {
    std::cout << "Usage: sound_processor -c <config.txt> <output.wav> <input1.wav> [<input2.wav> ...]\n"
        << "Parameters:\n"
        << "  -h                Show help information\n"
        << "  -c <config.txt>   Specify the configuration file with sound processing commands\n"
        << "  <output.wav>      Specify the output WAV file\n"
        << "  <input1.wav>      Specify at least one input WAV file\n"
        << "  [<input2.wav> ...] Specify additional input WAV files, if any\n";
}

void ParseConsole::Show_input_files(const std::vector<std::string>& input_files) {
    for (const auto& file : input_files) {
        std::cout << file << std::endl;
    }
}
