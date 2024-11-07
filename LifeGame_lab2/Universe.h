#ifndef UNIVERSE_H
#define UNIVERSE_H
#include <vector>
#include <string>
#include "Cell.h"
#include "ParseConsole.h"
#include <fstream>
#include <iostream>

class Universe {
private:
    int grid_size;                    // Размер вселенной (длина стороны квадратного поля)
    int currentIteration = 0;         // Текущая итерация игры
    std::string universe_rule;  // Правило перехода клеток, загружаемое из файла
    std::string universe_name;
    std::vector<std::vector<Cell>> grid; // Двумерный массив клеток, представляющий вселенную

    std::vector<int> birthConditions;    // Условия для рождения клеток
    std::vector<int> survivalConditions; // Условия для выживания клеток

    // Вспомогательные методы
    bool willBeAlive(int x, int y) const;       // Проверяет, будет ли клетка жива на следующем шаге
    int countAliveNeighbors(int x, int y) const; // Подсчитывает количество живых соседей
    void parseRule(const std::string& rule);    // Разбирает правило после загрузки из файла

public:
    // Конструктор, принимающий только размер вселенной
    Universe(int grid_size);

    // Метод для инициализации вселенной, возвращает true при успешной загрузке
    bool initialize(const ParseConsole& parser);

    // Метод для запуска в оффлайн-режиме (с заданным количеством итераций)
    void runOffline(int iterations, const std::string& outputFile = "");

    // Метод для запуска в онлайн-режиме (ожидает команды с консоли)
    void runOnline();

    // Основные методы для выполнения итераций и отображения состояния вселенной
    void tick(int iterations = 1);
    void display() const;

    // Методы для работы с отдельными клетками
    void setCell(int x, int y, bool alive);
    bool getCell(int x, int y) const;

    // Методы для сохранения и загрузки состояния вселенной из файлов
    bool saveToStream(std::ostream& os) const;
    bool loadFromStream(std::istream& is);

    friend std::istream& operator>>(std::istream& is, Universe& universe);
    friend std::ostream& operator<<(std::ostream& os, const Universe& universe);
    friend class TestUniverse;
};

#endif // UNIVERSE_H
