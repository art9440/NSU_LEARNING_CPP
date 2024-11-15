#include "ParseConsole.h"

ParseConsole::ParseConsole() : config_file("none"), output_file("none"), input_files(NULL),
use_help_(false) {}

std::vector<std::string> ParseConsole::get_input_files() const { return input_files; }
std::string ParseConsole::get_output_file() const { return output_file; }
bool ParseConsole::use_help() const { return use_help_; }
bool ParseConsole::hasConfig() const { return !config_file.empty(); }
std::string ParseConsole::get_config_file() const { return config_file; }

bool ParseConsole::parsing(int argc, char* argv[]) {
	if (argc < 5) {
		std::cerr << "Incorrect number of argument. Use -h for usage information." << std::endl;
		return false;
	}

	int index = 1;
	if (std::string(argv[index]) == "-c") {
		if (index + 1 < argc) {
			config_file = argv[++index];
		}
		else {
			std::cerr << "No config file." << std::endl;
			return false;
		}
		index++;
	}
	else if(std::string(argv[index]) == "-h") {
		use_help_ = true;
		help_me();
		return false;
	}
	else {
		std::cerr << "Can`t find flag -c. Use -h for usage information." << std::endl;
		return false;
	}

	if (index < argc) {
		output_file = argv[index++];
	}
	else {
		std::cerr << "No output_file." << std::endl;
		return false;
	}

	while (index < argc) {
		input_files.push_back(argv[index++]);
	}

	if (input_files.empty()) {
		std::cerr << "No input files." << std::endl;
		return false;
	}

	return true;
}

void ParseConsole::help_me() {
	std::cout << "�������������: sound_processor -c <config.txt> <output.wav> <input1.wav> [<input2.wav> ...]\n"
		<< "���������:\n"
		<< "  -h                �������� ������� �� ������������� ���������\n"
		<< "  -c <config.txt>   ������� ���� ������������ � ��������� ��������� �����\n"
		<< "  <output.wav>      ������� ��� ��������� WAV-�����\n"
		<< "  <input1.wav>      ������� ��� ������� ���� ������� WAV-����\n"
		<< "  [<input2.wav> ...] ������� �������������� ������� WAV-�����, ���� ��� ����\n";
}

void ParseConsole::Show_input_files(std::vector<std::string> input_files) {
	for (int i = 0; i < input_files.size(); i++) {
		std::cout << input_files[i] << std::endl;
	}
}