#include "ConverterFactory.h"
#include <sstream>
#include <iostream>

std::unique_ptr<Converter> ConverterFactory::createConverterFromLine(const std::string& line, 
    std::vector<WavFile>& inputWavs) {
    std::istringstream iss(line);
    std::string command;
    std::vector<int> params;

    // Извлекаем команду
    iss >> command;
    std::cout << "Command: " << command << std::endl;

    // Извлекаем параметры
    int param;
    while (iss >> param) {
        params.push_back(param);
        std::cout << "Parametr: " << param << std::endl;
    }

    // Обработка команд
    if (command == "mute") {
        if (params.size() < 2) {
            std::cerr << "Ошибка: недостаточно параметров для mute (требуется 2)." << std::endl;
            return nullptr;
        }
        return std::make_unique<MuteConverter>(params[0], params[1]);
    }
    else if (command == "mix") {
        if (params.size() < 2) {
            std::cerr << "Ошибка: недостаточно параметров для mix (требуется минимум 2)." << std::endl;
            return nullptr;
        }

        int fileIndex = params[1] - 1; // Индексация $n начинается с 1
        if (fileIndex < 0 || fileIndex >= static_cast<int>(inputWavs.size())) {
            std::cerr << "Error: Invalid file index for mix: " << params[1] << std::endl;
            return nullptr;
        }

        // Извлекаем дополнительный поток
        const std::vector<int16_t> additionalStream = inputWavs[fileIndex].getSamples();

        return std::make_unique<MixConverter> (additionalStream, params[0]);
    }
    else if (command == "echo") {
        if (params.size() < 1) {
            std::cerr << "Ошибка: недостаточно параметров для echo (требуется минимум 1)." << std::endl;
            return nullptr;
        }
        int delay = params[0];
        float decay = params.size() > 1 ? static_cast<float>(params[1]) / 100.0f : 0.5f;
        return  std::make_unique < EchoConverter> (delay, decay);
    }
    else {
        std::cerr << "Ошибка: неизвестная команда " << command << std::endl;
        return nullptr;
    }
}
