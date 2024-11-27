#ifndef PARSECONFIG_H
#define PARSECONFIG_H

#include <string>
#include <vector>

class ParseConfig {
public:
    // ������ ����� ������������ � ������� ������ �����
    bool readConfigFile(const std::string& filename, std::vector<std::string>& configLines);
};

#endif // PARSECONFIG_H

