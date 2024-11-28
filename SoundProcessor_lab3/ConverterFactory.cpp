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

    int param;
    std::string word;
    while (iss >> word) {
        // Проверяем, если это ссылка на файл (например, $2)
        if (word[0] == '$') {
            // Убираем '$' и конвертируем в число
            try {
                int fileIndex = std::stoi(word.substr(1)) - 1; // Индексация $n с 1, а массив с 0
                params.push_back(fileIndex);
                std::cout << "File index: " << fileIndex << std::endl;
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Invalid file index in config: " << word << std::endl;
                return nullptr; // Обрабатываем ошибку
            }
        }
        else {
            // Если это обычное число, просто добавляем в параметры
            try {
                param = std::stoi(word);
                params.push_back(param);
                std::cout << "Parameter: " << param << std::endl;
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Invalid parameter in config: " << word << std::endl;
                return nullptr;
            }
        }
    }


    // Обработка команд
    if (command == "mute") {
        if (params.size() < 2) {
            std::cerr << "Error: Not enough arguments for mute(need 2)." << std::endl;
            return nullptr;
        }
        return std::make_unique<MuteConverter>(params[0], params[1]);
    }
    else if (command == "mix") {
        if (params.size() < 2) {
            std::cerr << "Error: Not enough arguments for mix(need 2)." << std::endl;
            return nullptr;
        }

        int fileIndex = params[0];
        if (fileIndex < 0 || fileIndex >= static_cast<int>(inputWavs.size())) {
            std::cerr << "Error: Invalid file index " << fileIndex << " for mix command." << std::endl;
            return nullptr;
        }

        // Извлекаем дополнительный поток
        const std::vector<int16_t> additionalStream = inputWavs[fileIndex].getSamples();

        return std::make_unique<MixConverter> (additionalStream, params[0]);
    }
    else if (command == "echo") {
        if (params.size() < 1) {
            std::cerr << "Error: Not enough arguments for echo(minimum 1)." << std::endl;
            return nullptr;
        }
        int delay = params[0];
        float decay = params.size() > 1 ? static_cast<float>(params[1]) / 100.0f : 0.5f;
        return  std::make_unique < EchoConverter> (delay, decay);
    }
    else {
        std::cerr << "Error: Unknown command " << command << std::endl;
        return nullptr;
    }
}
