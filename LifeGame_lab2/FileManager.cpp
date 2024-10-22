#include "FileManager.h"

bool FileManager::read_from_file(std::string& filename, std::vector<std::vector<char>>& field,
	std::string& rule, std::string& universe_name) {
	std::ifstream input_file(filename);
	if (!input_file.is_open()) {
		std::cerr << "Error: could not open file." << filename << std::endl;
		return false;
	}
	std::string str;
	int row = 0;
	bool foundrule = false, founduniverse = false;
	while (getline(input_file, str)) {
		if (str[0] == '#') {
			if (row == 0 && str.substr(1) != "Life 1.06") {
				std::cerr << "Not a correct form of the file. Need to be Life 1.06." << std::endl;
				input_file.close();
				return false;
			}
			if (str[1] == 'N') {
				universe_name = str.substr(3);
				founduniverse = true;
			}
			if (str[1] == 'R') {
				rule = str.substr(3);
				foundrule = true;
			}
		}
		else {
			int x, y;
			if (sscanf(str.c_str(), "%d %d", &x, &y) == 2) {
				if (x >= 0 && y >= 0 && x < field.size() && y < field.size()) {
					field[x][y] = true;
				}
				else {
					std::cerr << "Coordinates out of range." << x << ',' << y << std::endl;
					return false;
				}
			}
			else {
				std::cerr << "Not correct form of coordinates" << str << std::endl;
			}
		}
	}
	if (foundrule == false) 
		std::cerr << "Can`t find rule in the file:" << filename << std::endl;
	if (founduniverse == false)
		std::cerr << "Can`t find universe in the file:" << filename << std::endl;
	return true;
}

void FileManager::save_to_file(const std::string& filename, const std::vector<std::vector<bool>>& field,
	const std::string& rule, const std::string& universe_name) {
	std::ofstream output_file(filename);
	if (!output_file.is_open()) {
		std::cerr << "Error: could not open file." << filename << std::endl;
		return;
	}
	output_file << "#Life 1.06" << std::endl;

}