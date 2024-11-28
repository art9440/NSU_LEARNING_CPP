#include "ParseConfig.h"
#include <fstream>
#include <iostream>

bool ParseConfig::readConfigFile(const std::string& filename, std::vector<std::string>& configLines) {
    std::ifstream config(filename);
    if (!config) {
        std::cerr << "������: �� ������� ������� ���� " << filename << " ��� ������." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(config, line)) {
        // ���������� ������ ������ � �����������
        if (line.empty() || line[0] == '#') continue;

        // ��������� ������ � ������
        configLines.push_back(line);
    }

    return true;
}
