#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

class Cell {
public:
    // Конструктор, задающий начальное состояние клетки
    Cell(bool is_alive = false) : alive(is_alive) {}

    // Метод для проверки, жива ли клетка
    bool isAlive() const { return alive; }

    // Метод для установки состояния клетки
    void setAlive(bool state) { alive = state; }

    // Переключение состояния клетки (опционально)
    void toggle() { alive = !alive; }

private:
    bool alive; // Состояние клетки: true - жива, false - мертва
}; 