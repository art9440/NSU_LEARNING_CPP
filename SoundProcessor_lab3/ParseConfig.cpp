#include "ParseConfig.h"
#include <fstream>
#include <iostream>

bool ParseConfig::readConfigFile(const std::string& filename, std::vector<std::string>& configLines) {
    std::ifstream config(filename);
    if (!config) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << " для чтения." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(config, line)) {
        // Пропускаем пустые строки и комментарии
        if (line.empty() || line[0] == '#') continue;

        // Добавляем строку в список
        configLines.push_back(line);
    }

    return true;
}
