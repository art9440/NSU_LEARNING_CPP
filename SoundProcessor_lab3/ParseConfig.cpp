#include "ParseConfig.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool ConfigParser::readConfigFile(const std::string& filename, std::vector<Converter*>& converters) {
    std::ifstream config(filename);
    if (!config) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << " для чтения." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(config, line)) {
        // Пропускаем пустые строки и комментарии
        if (line.empty() || line[0] == '#') continue;

        std::string command;
        std::vector<int> params;

        // Парсим строку и проверяем команду
        if (!parseLine(line, command, params)) {
            std::cerr << "Ошибка: неверная конфигурация в строке: " << line << std::endl;
            return false;
        }

        // Создаем конвертер на основе команды и параметров
        Converter* converter = createConverter(command, params);
        if (!converter) {
            std::cerr << "Ошибка: не удалось создать конвертер для команды: " << command << std::endl;
            return false;
        }

        converters.push_back(converter);
    }
    return true;
}

bool ConfigParser::parseLine(const std::string& line, std::string& command, std::vector<int>& params) {
    std::istringstream iss(line);
    iss >> command;

    // Проверка на допустимые команды
    if (command != "mix" && command != "mute" && command != "echo") {
        return false;
    }

    // Извлекаем параметры из строки
    int param;
    while (iss >> param) {
        params.push_back(param);
    }

    // Проверка параметров в зависимости от команды
    if (command == "mix") {
        return params.size() >= 2; // mix требует как минимум 2 параметра
    }
    else if (command == "mute") {
        return params.size() == 2; // mute требует ровно 2 параметра
    }
    else if (command == "echo") {
        return params.size() >= 1; // echo требует как минимум 1 параметр
    }
    return false;
}

Converter* ConfigParser::createConverter(const std::string& command, const std::vector<int>& params) {
    if (command == "mute") {
        // Создаем MuteConverter с параметрами start и end
        return new MuteConverter(params[0], params[1]);
    }
    else if (command == "mix") {
        // Создаем MixConverter. Требуется дополнительный поток (например, params[1] указывает на индекс)
        // Здесь нужно получить дополнительный поток, например, из inputWavs
        // Допустим, что это упрощенный пример
        std::vector<int16_t> additionalStream; // Нужно передать настоящий поток
        return new MixConverter(additionalStream, params[0]);
    }
    else if (command == "echo") {
        // Создаем EchoConverter с параметрами delay и decay
        int delay = params[0];
        float decay = params.size() > 1 ? static_cast<float>(params[1]) / 100.0f : 0.5f;
        return new EchoConverter(delay, decay);
    }
    return nullptr;
}
