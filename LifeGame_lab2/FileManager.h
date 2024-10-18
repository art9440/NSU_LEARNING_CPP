#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

class FileManager {
public:
	static bool read_from_file(std::string& filename, std::vector<std::vector<char>>& field,
		std::string& rule, std::string& unverse_name);
	static void save_to_file(const std::string& filename, const std::vector<std::vector<bool>>& field,
		const std::string& rule, const std::string& universe_name);

};