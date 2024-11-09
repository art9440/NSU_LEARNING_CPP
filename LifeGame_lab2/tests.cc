#include "Universe.h"
#include <gtest/gtest.h>
#include <fstream>


TEST(GameTests, InitializeTest) {
    std::ofstream file("test1.txt");
    file << "Life 1.06\n";
    file << "#N Test\n";
    file << "#R B3/S23\n";
    file << "1 1\n";
    file << "2 1\n";
    file << "2 2\n";
    file << "1 2\n";
    file.close();

    
    const char* argv[] = { "program", "-f", "test1.txt" };
    int argc = 3;
    ParseConsole parser;
    parser.parsing(argc, const_cast<char**>(argv));

    
    Universe universe(5);
    ASSERT_TRUE(universe.initialize(parser));  

    
    ASSERT_TRUE(universe.getCell(1, 1));
    ASSERT_TRUE(universe.getCell(2, 1));
    ASSERT_TRUE(universe.getCell(2, 2));
    ASSERT_TRUE(universe.getCell(1, 2));

    
    ASSERT_FALSE(universe.getCell(0, 0));
    ASSERT_FALSE(universe.getCell(4, 4));

    
    std::remove("test1.txt");
}


TEST(GameTests, RunOfflineTest) {
    std::ofstream inputFile("test_input.txt");
    inputFile << "Life 1.06\n";
    inputFile << "#N Test Universe\n";
    inputFile << "#R B3/S23\n";
    inputFile << "1 0\n";
    inputFile << "1 1\n";
    inputFile << "1 2\n";  // Осциллятор ("блинкер")
    inputFile.close();

    const char* argv[] = { "program", "-f", "test_input.txt", "-o", "test_output.txt", "-i", "2", "-m", "offline"};
    int argc = 9;
    ParseConsole parser;
    parser.parsing(argc, const_cast<char**>(argv));

    
    Universe universe(5);
    universe.initialize(parser);  
    universe.runOffline(2, "test_output.txt");

    std::ifstream outputFile("test_output.txt");
    ASSERT_TRUE(outputFile.is_open());

    std::string line;
    std::getline(outputFile, line);
    ASSERT_EQ(line, "Life 1.06");

    std::getline(outputFile, line);
    ASSERT_EQ(line, "#N Test Universe");

    std::getline(outputFile, line);
    ASSERT_EQ(line, "#R B3/S23");

    // Проверка итогового состояния клеток после двух итераций
    std::vector<std::pair<int, int>> expectedAliveCells = { {1, 0}, {1, 1}, {1, 2} };
    for (const auto& cell : expectedAliveCells) {
        int x, y;
        outputFile >> x >> y;
        ASSERT_EQ(x, cell.first);
        ASSERT_EQ(y, cell.second);
    }

    outputFile.close(); 

    std::remove("test_input.txt");
    std::remove("test_output.txt");
}

void TestWillBeAlive_SurvivalTest() {
    Universe universe(5);
    universe.parseRule("B3/S23"); 

    universe.setCell(1, 1, true);
    universe.setCell(1, 2, true);
    universe.setCell(2, 1, true);

    ASSERT_TRUE(universe.willBeAlive(1, 1));

    universe.setCell(2, 2, true);

    ASSERT_TRUE(universe.willBeAlive(1, 1));
}

void TestWillBeAlive_BirthTest() {
    Universe universe(5);
    universe.parseRule("B3/S23");

    universe.setCell(1, 1, false);
    universe.setCell(0, 0, true);
    universe.setCell(0, 1, true);
    universe.setCell(1, 0, true);

    ASSERT_TRUE(universe.willBeAlive(1, 1));
}


TEST(GameTests, WillBeAlive_SurvivalTest) {
    TestWillBeAlive_SurvivalTest();
}

TEST(GameTests, WillBeAlive_BirthTest) {
    TestWillBeAlive_BirthTest();
}

void TestCountAliveNeighbors_AllNeighbors() {
    Universe universe(5);

    
    universe.setCell(1, 1, true);
    universe.setCell(1, 2, true);
    universe.setCell(1, 3, true);
    universe.setCell(2, 1, true);
    universe.setCell(2, 3, true);
    universe.setCell(3, 1, true);
    universe.setCell(3, 2, true);
    universe.setCell(3, 3, true);

    
    ASSERT_EQ(universe.countAliveNeighbors(2, 2), 8);
}

void TestCountAliveNeighbors_EdgeWrapping() {
    Universe universe(5);

    universe.setCell(0, 0, true);
    universe.setCell(4, 4, true);

    ASSERT_EQ(universe.countAliveNeighbors(0, 0), 1);

    ASSERT_EQ(universe.countAliveNeighbors(4, 4), 1);
}

TEST(GameTests, CountAliveNeighborsAllNeighbors) {
    TestCountAliveNeighbors_AllNeighbors();
}

TEST(GameTests, CountAliveNeighborsEdgeWrapping) {
    TestCountAliveNeighbors_EdgeWrapping();
}