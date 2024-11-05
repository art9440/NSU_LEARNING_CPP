#include "Universe.h"


Universe::Universe(int grid_size) : grid_size(grid_size), 
grid(grid_size, std::vector<Cell>(grid_size)) {}

bool Universe::initialize(const ParseConsole& parser) {
    std::string inputFile = parser.get_input_file();

    if (!inputFile.empty() && inputFile != "none") {
        if (!loadFromFile(inputFile)) {
            std::cerr << "Error: Failed to load universe from file: " << inputFile << "\n";
            return false;
        }
        else {
            std::cout << "Loaded universe from file: " << inputFile << "\n";
            return true;
        }
    }
    else {
        std::cerr << "Error: No input file provided for universe initialization.\n";
        return false;
    }
}

bool Universe::loadFromFile(const std::string& filename) {
    std::ifstream input_file(filename);
    if (!input_file.is_open()) {
        std::cerr << "Error: could not open file: " << filename << std::endl;
        return false;
    }

    std::string str;
    bool found_rule = false, found_universe = false;

    // Проверка формата первой строки
    if (getline(input_file, str)) {
        if (str != "Life 1.06") {
            std::cerr << "Error: incorrect file format, expected 'Life 1.06' header." << std::endl;
            return false;
        }
    }
    else {
        std::cerr << "Error: file is empty or cannot read: " << filename << std::endl;
        return false;
    }

    // Основной цикл чтения файла
    while (getline(input_file, str)) {
        if (str[0] == '#') {
            if (str[1] == 'N') {
                universe_name = str.substr(3);
                found_universe = true;
            }
            else if (str[1] == 'R') {
                universe_rule = str.substr(3);
                found_rule = true;
            }
        }
        else {
            int x, y;
            if (sscanf(str.c_str(), "%d %d", &x, &y) == 2) {
                if (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size()) {
                    grid[x][y] = true;
                }
                else {
                    std::cerr << "Error: coordinates out of range: " << x << ',' << y << std::endl;
                    return false;
                }
            }
            else {
                std::cerr << "Error: incorrect format for coordinates: " << str << std::endl;
            }
        }

        
    }
    //Предупреждения о пропущенных параметрах
    if (!found_rule)
        std::cerr << "Warning: missing rule in the file: " << filename << std::endl;
    if (!found_universe)
        std::cerr << "Warning: missing universe name in the file: " << filename << std::endl;

    return true;
}


void Universe::runOffline(int iterations, const std::string& outputFile) {
    std::cout << "Starting offline run for " << iterations << " iterations.\n";
    tick(iterations);
    display();
    if (!outputFile.empty()) {
        if (saveToFile(outputFile)) {
            std::cout << "Saved final universe state to " << outputFile << "\n";
        }
        else {
            std::cerr << "Error: Failed to save universe to file " << outputFile << "\n";
        }
    }
}


void Universe::tick(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        std::vector<std::vector<Cell>> newGrid = grid;

        for (int x = 0; x < grid_size; ++x) {
            for (int y = 0; y < grid_size; ++y) {
                newGrid[x][y].setAlive(willBeAlive(x, y));
            }
        }
        grid = newGrid;
        currentIteration++; // Увеличиваем счётчик текущей итерации
    }
}

bool Universe::willBeAlive(int x, int y) const {
    int aliveNeighbors = countAliveNeighbors(x, y);
    if (grid[x][y].isAlive()) {
        return std::find(survivalConditions.begin(), survivalConditions.end(), aliveNeighbors) != survivalConditions.end();
    }
    else {
        return std::find(birthConditions.begin(), birthConditions.end(), aliveNeighbors) != birthConditions.end();
    }
}

int Universe::countAliveNeighbors(int x, int y) const {
    int count = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int nx = (x + dx + grid_size) % grid_size;
            int ny = (y + dy + grid_size) % grid_size;
            if (grid[nx][ny].isAlive()) ++count;
        }
    }
    return count;
}

void Universe::parseRule(const std::string& rule) {
    birthConditions.clear();
    survivalConditions.clear();
    bool birthMode = false;

    for (char ch : rule) {
        if (ch == 'B') {
            birthMode = true;
        }
        else if (ch == 'S') {
            birthMode = false;
        }
        else if (isdigit(ch)) {
            int condition = ch - '0';
            if (birthMode) {
                birthConditions.push_back(condition);
            }
            else {
                survivalConditions.push_back(condition);
            }
        }
    }
}

void Universe::display() const {
    for (int y = 0; y < grid_size; ++y) {
        for (int x = 0; x < grid_size; ++x) {
            std::cout << (grid[x][y].isAlive() ? 'O' : '.');
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}

void Universe::setCell(int x, int y, bool alive) {
    if (x >= 0 && x < grid_size && y >= 0 && y < grid_size) {
        grid[x][y].setAlive(alive);
    }
}

bool Universe::getCell(int x, int y) const {
    return x >= 0 && x < grid_size && y >= 0 && y < grid_size ? grid[x][y].isAlive() : false;
}

void Universe::runOnline() {
    std::string command;
    display();
    while (true) {
        std::cout << "Enter command (tick <n>, dump <file>, exit): ";
        std::cin >> command;

        if (command == "exit") {
            break;
        }
        else if (command == "tick") {
            int n = 1;
            if (std::cin.peek() == ' ') std::cin >> n;
            tick(n);
            display();
        }
        else if (command == "dump") {
            std::string file;
            std::cin >> file;
            if (saveToFile(file)) {
                std::cout << "Saved universe to " << file << "\n";
            }
        }
        else {
            std::cout << "Unknown command. Try again.\n";
        }
    }
}


bool Universe::saveToFile(const std::string& filename) const {
    std::ofstream output_file(filename);
    if (!output_file.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << filename << std::endl;
        return false;
    }

    output_file << "Life 1.06\n";
    output_file << "#N " << universe_name << "\n";
    output_file << "#R " << universe_rule << "\n";

    for (int x = 0; x < grid_size; ++x) {
        for (int y = 0; y < grid_size; ++y) {
            if (grid[x][y].isAlive()) {
                output_file << x << " " << y << "\n";
            }
        }
    }

    output_file.close();
    std::cout << "File saved successfully: " << filename << std::endl;  // Добавьте эту строку
    return true;
}

