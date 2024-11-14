#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>


class ParseConsole {
public:
	ParseConsole();
	bool parsing(int argc, char* argv[]);
	void help_me();
	std::vector<std::string> get_input_files() const;
	std::string get_output_file() const;
	bool hasConfig() const;
	bool use_help() const;
private:
	std::vector<std::string> input_files;
	std::string output_file;
	bool use_help_ = false;
	std::string config_file;
};