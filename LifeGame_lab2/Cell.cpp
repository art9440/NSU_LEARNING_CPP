#include "Cell.h"

Cell::Cell(bool is_alive) : alive(is_alive) {}

bool Cell::isAlive() const {
    return alive;
}

void Cell::setAlive(bool state) {
    alive = state;
}

void Cell::toggle() {
    alive = !alive;
}
