#include "Universe.h"
#include <gtest/gtest.h>
#include <fstream>
#include <sstream>

TEST(UniverseTest, LoadFromFile) {
    Universe universe(5);

    std::stringstream input(
        "Life 1.06\n"
        "#N Test Universe\n"
        "#R B3/S23\n"
        "1 1\n"
        "2 1\n"
        "2 2\n"
        "1 2\n"
    );

    input >> universe; // Загрузка вселенной из потока

    ASSERT_TRUE(universe.getCell(1, 1));
    ASSERT_TRUE(universe.getCell(2, 1));
    ASSERT_TRUE(universe.getCell(2, 2));
    ASSERT_TRUE(universe.getCell(1, 2));
    ASSERT_FALSE(universe.getCell(0, 0)); // Пустая клетка
}

TEST(UniverseTest, SaveToFile) {
    Universe universe(5);
    universe.setCell(1, 1, true);
    universe.setCell(2, 1, true);
    universe.setCell(2, 2, true);
    universe.setCell(1, 2, true);

    std::stringstream output;
    output << universe; // Сохранение вселенной в поток

    std::string expectedOutput =
        "Life 1.06\n"
        "#N \n"
        "#R \n"
        "1 1\n"
        "2 1\n"
        "2 2\n"
        "1 2\n";

    ASSERT_EQ(output.str(), expectedOutput);
}

//TEST(UniverseTest, TickRuleApplication) {
//    Universe universe(5);
//    universe.parseRule("B3/S23");
//
//    // Настраиваем "блок" - структура, которая должна оставаться стабильной
//    universe.setCell(1, 1, true);
//    universe.setCell(1, 2, true);
//    universe.setCell(2, 1, true);
//    universe.setCell(2, 2, true);
//
//    universe.tick(1);
//
//    // Убедитесь, что "блок" остался стабильным
//    ASSERT_TRUE(universe.getCell(1, 1));
//    ASSERT_TRUE(universe.getCell(1, 2));
//    ASSERT_TRUE(universe.getCell(2, 1));
//    ASSERT_TRUE(universe.getCell(2, 2));
//    ASSERT_FALSE(universe.getCell(0, 0));
//}
//
//TEST(UniverseTest, OscillatorBehavior) {
//    Universe universe(5);
//    universe.parseRule("B3/S23");
//
//    // Настраиваем "блинкер" - осциллирующая структура
//    universe.setCell(1, 2, true);
//    universe.setCell(2, 2, true);
//    universe.setCell(3, 2, true);
//
//    universe.tick(1);
//
//    // После одного тик клетки должны сменить положение
//    ASSERT_FALSE(universe.getCell(1, 2));
//    ASSERT_TRUE(universe.getCell(2, 1));
//    ASSERT_TRUE(universe.getCell(2, 2));
//    ASSERT_TRUE(universe.getCell(2, 3));
//
//    universe.tick(1);
//
//    // Должны вернуться в исходное состояние
//    ASSERT_TRUE(universe.getCell(1, 2));
//    ASSERT_TRUE(universe.getCell(2, 2));
//    ASSERT_TRUE(universe.getCell(3, 2));
//    ASSERT_FALSE(universe.getCell(2, 1));
//    ASSERT_FALSE(universe.getCell(2, 3));
//}

TEST(UniverseTest, LoadAndSaveStreamOperators) {
    Universe universe(5);

    std::stringstream input(
        "Life 1.06\n"
        "#N Test Universe\n"
        "#R B3/S23\n"
        "1 1\n"
        "1 2\n"
        "2 2\n"
        "2 1\n"
    );

    input >> universe;

    std::stringstream output;
    output << universe;

    std::string expectedOutput =
        "Life 1.06\n"
        "#N Test Universe\n"
        "#R B3/S23\n"
        "1 1\n"
        "1 2\n"
        "2 1\n"
        "2 2\n";

    ASSERT_EQ(output.str(), expectedOutput);
}
