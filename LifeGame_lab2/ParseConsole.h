#ifndef PARSECONSOLE_H
#define PARSECONSOLE_H

#include <string>

class ParseConsole {
private:
    std::string input_file;
    std::string output_file;
    int iterations;
    bool mode;
    bool use_help_ = false;

public:
    ParseConsole();
    bool parsing(int argc, char* argv[]);
    void help_me();
    int get_iterations() const;
    bool get_mode() const;
    std::string get_input_file() const;
    std::string get_output_file() const;
    bool use_help() const;
};

#endif // PARSECONSOLE_H
