#ifndef PARSECONFIG_H
#define PARSECONFIG_H

#include <string>
#include <vector>

class ParseConfig {
public:
    // Чтение файла конфигурации и возврат списка строк
    bool readConfigFile(const std::string& filename, std::vector<std::string>& configLines);
};

#endif // PARSECONFIG_H

