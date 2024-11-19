#include <vector>
#include <string>
#include "Converter.h"

class ConfigParser {
public:
    // Метод для чтения конфигурационного файла и создания конвертеров
    bool readConfigFile(const std::string& filename, std::vector<Converter*>& converters);

private:
    // Метод для проверки строки конфигурации и извлечения типа команды
    bool parseLine(const std::string& line, std::string& command, std::vector<int>& params);

    // Метод для создания конвертера на основе команды и параметров
    Converter* createConverter(const std::string& command, const std::vector<int>& params);
};

