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
        // Проверяем количество параметров
        if (params.size() < 2) {
            std::cerr << "Ошибка: недостаточно параметров для mute (требуется 2)." << std::endl;
            return nullptr;
        }
        return new MuteConverter(params[0], params[1]); // start и end
    }
    else if (command == "mix") {
        // Проверяем параметры
        if (params.size() < 2) {
            std::cerr << "Ошибка: недостаточно параметров для mix (требуется минимум 2)." << std::endl;
            return nullptr;
        }
        std::vector<int16_t> additionalStream; // TODO: передать настоящий поток
        return new MixConverter(additionalStream, params[0]); // Дополнительный поток и позиция вставки
    }
    else if (command == "echo") {
        // Проверяем параметры
        if (params.size() < 1) {
            std::cerr << "Ошибка: недостаточно параметров для echo (требуется минимум 1)." << std::endl;
            return nullptr;
        }
        int delay = params[0];
        float decay = params.size() > 1 ? static_cast<float>(params[1]) / 100.0f : 0.5f;
        return new EchoConverter(delay, decay);
    }
    std::cerr << "Ошибка: неизвестная команда " << command << std::endl;
    return nullptr;
}

