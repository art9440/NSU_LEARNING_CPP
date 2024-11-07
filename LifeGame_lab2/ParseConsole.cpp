#include "ParseConsole.h"
#include <iostream>
#include <cstring>

ParseConsole::ParseConsole() : iterations(0), mode(false),
input_file("none"), output_file("none"), use_help_(false) {}

int ParseConsole::get_iterations() const { return iterations; }
bool ParseConsole::get_mode() const { return mode; }
std::string ParseConsole::get_input_file() const { return input_file; }
std::string ParseConsole::get_output_file() const { return output_file; }
bool ParseConsole::use_help() const { return use_help_; }

bool ParseConsole::parsing(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0) {
            if (i + 1 < argc)
                input_file = std::string(argv[++i]);
            else {
                std::cerr << "Error: Missing input file name. Use -h or --help for usage information." << std::endl;
                return false;
            }
        }
        else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            if (i + 1 < argc)
                output_file = std::string(argv[++i]);
            else {
                std::cerr << "Error: Missing output file name. Use -h or --help for usage information." << std::endl;
                return false;
            }
        }
        else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--iterations") == 0) {
            if (i + 1 < argc) {
                try {
                    iterations = std::stoul(argv[++i]);
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "Error: Invalid value for iterations. Use -h or --help for usage information." << std::endl;
                    return false;
                }
            }
            else {
                std::cerr << "Error: Missing number of iterations. Use -h or --help for usage information." << std::endl;
                return false;
            }
        }
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            help_me();
            use_help_ = true;
            return false;
        }
        else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--mode") == 0) {
            if (i + 1 < argc) {
                if (strcmp(argv[++i], "offline") == 0)
                    mode = true;
                else if (strcmp(argv[i], "online") == 0)
                    mode = false;
                else {
                    std::cerr << "Error: Unrecognized mode. Use -h or --help for usage information." << std::endl;
                    return false;
                }
            }
            else {
                std::cerr << "Error: Missing mode value. Use -h or --help for usage information." << std::endl;
                return false;
            }
        }
        else {
            std::cerr << "Error: Unrecognized command. Use -h or --help for usage information." << std::endl;
            return false;
        }
    }
    if (!mode && iterations == 0)
        iterations = 1;

    return true;
}

void ParseConsole::help_me() {
    std::cout << "Game of Life - User Help\n\n";
    std::cout << "Available commands and command-line arguments:\n\n";

    std::cout << "Command-line arguments:\n";
    std::cout << "  -i <number> or --iterations=<number> : Set the number of iterations to calculate. If specified,\n"
        << "     the program will immediately calculate the specified number of iterations after starting.\n";
    std::cout << "  -o <file> or --output=<file>         : Set the file name for saving the universe state after iterations.\n";
    std::cout << "  -f <file> or --file=<file>           : Specify an input file to load the universe state.\n"
        << "     If no file is specified, a new random universe will be created.\n";
    std::cout << "  -m <mode> or --mode=<mode>           : Set the mode of operation. Possible values:\n"
        << "        offline - The program will calculate the specified number of iterations without further interaction.\n"
        << "        online  - The program will enter interactive mode after calculating the specified iterations.\n";
    std::cout << "  -h or --help                         : Display this help message.\n\n";

    std::cout << "Example usage:\n";
    std::cout << "  ./game_of_life -i 10 -o output.txt -f input.txt -m offline\n\n";

    std::cout << "Interactive mode commands (available only in online mode):\n";
    std::cout << "  tick <n=1> or t <n=1>               : Calculate n iterations (default is 1) and display the universe state.\n";
    std::cout << "  dump <file name>                    : Save the current universe state to the specified file.\n";
    std::cout << "  exit                                : Exit the game.\n";
    std::cout << "  help                                : Display this help message with a list of all commands.\n\n";

    std::cout << "Examples of commands in interactive mode:\n";
    std::cout << "  tick 5             - Calculate 5 iterations and display the result.\n";
    std::cout << "  dump universe.txt  - Save the current state to the file universe.txt.\n";
    std::cout << "  exit               - Exit the program.\n";
    std::cout << "  help               - Display this help message with available commands.\n";
}
