//#include "FileManager.h"
//
//bool FileManager::read_from_file(std::string& filename, std::vector<std::vector<bool>>& field,
//    std::string& rule, std::string& universe_name) {
//
//    std::ifstream input_file(filename);
//    if (!input_file.is_open()) {
//        std::cerr << "Error: could not open file: " << filename << std::endl;
//        return false;
//    }
//
//    std::string str;
//    bool found_rule = false, found_universe = false;
//
//    // Проверка формата первой строки
//    if (getline(input_file, str)) {
//        if (str != "Life 1.06") {
//            std::cerr << "Error: incorrect file format, expected 'Life 1.06' header." << std::endl;
//            return false;
//        }
//    }
//    else {
//        std::cerr << "Error: file is empty or cannot read: " << filename << std::endl;
//        return false;
//    }
//
//    // Основной цикл чтения файла
//    while (getline(input_file, str)) {
//        if (str[0] == '#') {
//            if (str[1] == 'N') {
//                universe_name = str.substr(3);
//                found_universe = true;
//            }
//            else if (str[1] == 'R') {
//                rule = str.substr(3);
//                found_rule = true;
//            }
//        }
//        else {
//            int x, y;
//            if (sscanf(str.c_str(), "%d %d", &x, &y) == 2) {
//                if (x >= 0 && x < field.size() && y >= 0 && y < field[0].size()) {
//                    field[x][y] = true;
//                }
//                else {
//                    std::cerr << "Error: coordinates out of range: " << x << ',' << y << std::endl;
//                    return false;
//                }
//            }
//            else {
//                std::cerr << "Error: incorrect format for coordinates: " << str << std::endl;
//            }
//        }
//    }
//
//    // Предупреждения о пропущенных параметрах
//    if (!found_rule)
//        std::cerr << "Warning: missing rule in the file: " << filename << std::endl;
//    if (!found_universe)
//        std::cerr << "Warning: missing universe name in the file: " << filename << std::endl;
//
//    return true;
//}
//
//
//bool FileManager::save_to_file(const std::string& filename, const std::vector<std::vector<bool>>& field,
//	const std::string& rule, const std::string& universe_name) {
//	std::ofstream output_file(filename);
//	if (!output_file.is_open()) {
//		std::cerr << "Error: could not open file." << filename << std::endl;
//		return;
//	}
//	output_file << "#Life 1.06" << std::endl;
//    output_file << "#N" << universe_name << std::endl;
//    output_file << "#R" << rule << std::endl;
//    for (size_t x = 0; x < field.size(); ++x) {
//        for (size_t y = 0; y < field[x].size(); ++y) {
//            if (field[x][y]) {
//                output_file << x << " " << y << "\n";
//            }
//        }
//    }
//
//    output_file.close();
//    return true;
//}