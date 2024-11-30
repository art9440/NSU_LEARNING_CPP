#include "ConverterFactory.h"
#include <sstream>
#include <iostream>
#include "Exceptions.h"

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
                throw InvalidParameterException(word);  // Неверный параметр
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
                throw InvalidParameterException(word);  // Неверный параметр
            }
        }
    }

    // Обработка команд
    if (command == "mute") {
        if (params.size() < 2) {
            throw ConverterInsufficientArgumentsException("mute", 2);  // Недостаточно аргументов для mute
        }
        return std::make_unique<MuteConverter>(params[0], params[1]);
    }
    else if (command == "mix") {
        if (params.size() < 2) {
            throw ConverterInsufficientArgumentsException("mix", 2);  // Недостаточно аргументов для mix
        }

        int fileIndex = params[0];
        if (fileIndex < 0 || fileIndex >= static_cast<int>(inputWavs.size())) {
            throw InvalidFileIndexException(fileIndex);  // Неверный индекс файла для mix
        }

        // Извлекаем дополнительный поток
        const std::vector<int16_t> additionalStream = inputWavs[fileIndex].getSamples();
        return std::make_unique<MixConverter>(additionalStream, params[1]);
    }
    else if (command == "echo") {
        if (params.size() < 1) {
            throw ConverterInsufficientArgumentsException("echo", 1);  // Недостаточно аргументов для echo
        }
        int delay = params[0];
        float decay = params.size() > 1 ? static_cast<float>(params[1]) / 100.0f : 0.5f;
        return std::make_unique<EchoConverter>(delay, decay);
    }
    else {
        throw UnknownCommandException(command);  // Неизвестная команда
    }
}
