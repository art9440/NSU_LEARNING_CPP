#include "ParseConsole.h"
#include "Universe.h"
#include <iostream>

int main(int argc, char* argv[]) {
    ParseConsole parser;

    // Парсим аргументы командной строки
    if (!parser.parsing(argc, argv)) {
        if (parser.use_help()) {
            return 0;
        }
        else {
            std::cerr << "Error: Failed to parse command line arguments." << std::endl;
            return 1;
        }
    }

    // Отладка параметров
    std::cout << "Input file: " << parser.get_input_file() << "\n";
    std::cout << "Output file: " << parser.get_output_file() << "\n";
    std::cout << "Iterations: " << parser.get_iterations() << "\n";
    std::cout << "Mode (offline=true, online=false): " << parser.get_mode() << "\n";

    // Создаем вселенную
    int grid_size = 20; // Размер вселенной
    Universe universe(grid_size);

    // Инициализируем вселенную, передавая parser
    if (!universe.initialize(parser)) {
        std::cerr << "Error: Universe initialization failed.\n";
        return 1;
    }
    std::cout << "Universe initialized successfully.\n";

    // Запускаем в нужном режиме
    if (parser.get_mode()) {
        std::cout << "Running in offline mode...\n";
        universe.runOffline(parser.get_iterations(), parser.get_output_file());
    }
    else {
        std::cout << "Running in online mode...\n";
        universe.runOnline();
    }

    return 0;
}
