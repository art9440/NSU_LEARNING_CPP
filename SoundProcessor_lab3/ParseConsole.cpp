#include "ParseConsole.h"

ParseConsole::ParseConsole() : config_file("none"), output_file("none"), input_files(NULL),
use_help_(false) {}

std::vector<std::string> ParseConsole::get_input_files() const { return input_files; }
std::string ParseConsole::get_output_file() const { return output_file; }
bool ParseConsole::use_help() const { return use_help_; }
bool ParseConsole::hasConfig() const { return !config_file.empty(); }

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
}

void ParseConsole::help_me() {
	std::cout << "Использование: sound_processor -c <config.txt> <output.wav> <input1.wav> [<input2.wav> ...]\n"
		<< "Параметры:\n"
		<< "  -h                Показать справку по использованию программы\n"
		<< "  -c <config.txt>   Указать файл конфигурации с командами обработки звука\n"
		<< "  <output.wav>      Указать имя выходного WAV-файла\n"
		<< "  <input1.wav>      Указать как минимум один входной WAV-файл\n"
		<< "  [<input2.wav> ...] Указать дополнительные входные WAV-файлы, если они есть\n";
}