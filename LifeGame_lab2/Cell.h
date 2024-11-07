#ifndef CELL_H
#define CELL_H

class Cell {
private:
    bool alive; // true, если клетка жива; false, если мертва
public:
    // Конструктор по умолчанию создает мертвую клетку
    Cell(bool is_alive = false);

    // Возвращает true, если клетка жива
    bool isAlive() const;

    // Устанавливает состояние клетки (жива/мертва)
    void setAlive(bool state);

    // Переключает состояние клетки (если была жива — становится мертвой, и наоборот)
    void toggle();


};

#endif // CELL_H

