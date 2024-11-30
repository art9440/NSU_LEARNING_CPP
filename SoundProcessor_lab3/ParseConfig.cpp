#include "ParseConfig.h"
#include <fstream>
#include <iostream>
#include "Exceptions.h"

bool ParseConfig::readConfigFile(const std::string& filename, std::vector<std::string>& configLines) {
    std::ifstream config(filename);
    if (!config) {
        throw ConfigFileOpenException(filename);
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
