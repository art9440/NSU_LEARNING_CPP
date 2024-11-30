#include <stdexcept>
#include <string>

//Базовая ошибка
class SoundProcessorException : public std::runtime_error {
public:
    explicit SoundProcessorException(const std::string& message)
        : std::runtime_error(message) {}
};

//Ошибки парсинга консоли

class ParseConsoleException : public SoundProcessorException {
public:
    explicit ParseConsoleException(const std::string& message)
        : SoundProcessorException("ConsoleParser error: " + message) {}
};

// Ошибка: отсутствие флага -c
class MissingFlagException : public ParseConsoleException {
public:
    explicit MissingFlagException()
        : ParseConsoleException("Missing flag '-c'. Use -h for usage information.") {}
};

// Ошибка: неправильное использование флага -h
class InvalidHelpFlagException : public ParseConsoleException {
public:
    explicit InvalidHelpFlagException()
        : ParseConsoleException("Invalid usage of '-h'. Use -c <config.txt> for configuration.") {}
};

// Ошибка: недостаточно аргументов
class ParseInsufficientArgumentsException : public ParseConsoleException {
public:
    explicit ParseInsufficientArgumentsException()
        : ParseConsoleException("Insufficient arguments. Use -h for usage information.") {}
};

// Ошибка: отсутствие входных файлов
class MissingInputFilesException : public ParseConsoleException {
public:
    explicit MissingInputFilesException()
        : ParseConsoleException("No input files specified.") {}
};

// Ошибка: отсутствие выходного файла
class MissingOutputFileException : public ParseConsoleException {
public:
    explicit MissingOutputFileException()
        : ParseConsoleException("No output file specified.") {}
};

// Ошибка: конфигурационный файл не найден или неверный формат
class InvalidConfigFileException : public ParseConsoleException {
public:
    explicit InvalidConfigFileException()
        : ParseConsoleException("No configuration file specified or invalid format.") {}
};

//Ошибки конфигурационного файла

class ParseConfigException : public SoundProcessorException {
public:
    explicit ParseConfigException(const std::string& message)
        : SoundProcessorException("Parse Config Error: " + message) {}
};



class ConfigFileOpenException : public ParseConfigException {
public:
    explicit ConfigFileOpenException(const std::string& filename)
        : ParseConfigException("Failed to open config file: " + filename) {}
};

//Ошибки Фабрики

class ConverterException : public SoundProcessorException {
public:
    explicit ConverterException(const std::string& message)
        : SoundProcessorException("Converter Error: " + message) {}
};

// Ошибка: Неверный индекс файла для команды mix
class InvalidFileIndexException : public ConverterException {
public:
    explicit InvalidFileIndexException(int fileIndex)
        : ConverterException("Invalid file index: " + std::to_string(fileIndex)) {}
};


// Ошибка: Неверный параметр в конфигурации
class InvalidParameterException : public ConverterException {
public:
    explicit InvalidParameterException(const std::string& param)
        : ConverterException("Invalid parameter: " + param) {}
};

// Ошибка: Недостаточно аргументов для команды
class ConverterInsufficientArgumentsException : public ConverterException {
public:
    explicit ConverterInsufficientArgumentsException(const std::string& command, int requiredArgs)
        : ConverterException("Not enough arguments for " + command + " (need " + std::to_string(requiredArgs) + ").") {}
};

// Ошибка: Неизвестная команда
class UnknownCommandException : public ConverterException {
public:
    explicit UnknownCommandException(const std::string& command)
        : ConverterException("Unknown command: " + command) {}
};

class WavFileException : public SoundProcessorException {
public:
    explicit WavFileException(const std::string& message)
        : SoundProcessorException("WavFile Error:" + message) {}
};

class WavFileOpenException : public WavFileException {
public:
    explicit WavFileOpenException(const std::string& filename, const std::string& mode)
        : WavFileException("Error: Failed to open file '" + filename + "' for " + mode + ".") {}
};

class InvalidWavFormatException : public WavFileException {
public:
    explicit InvalidWavFormatException(const std::string& filename)
        : WavFileException("Error: Invalid WAV format in file : " + filename) {}
};

class WavFileReadException : public WavFileException {
public:
    explicit WavFileReadException(const std::string& filename) 
    : WavFileException("Error: Failed to read from file: " + filename) {}
};

class MissingSubchunkException : public WavFileException {
public:
    explicit MissingSubchunkException(const std::string& filename, const std::string& subchunk)
        : WavFileException("Error: Missing '" + subchunk + "' subchunk in file: " + filename) {}
};


class FileWriteException : public WavFileException {
public:
    explicit FileWriteException(const std::string& filename)
        : WavFileException("Error: Failed to write to file: " + filename) {}
};



