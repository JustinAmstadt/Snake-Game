#include <iostream>

#include "Cell.hpp"

Cell::Cell() {
    std::cout << "WARNING: Setting a Cell value to -1, -1!!" << std::endl;
    Cell(-1, -1);
}

Cell::Cell(int x, int y) {
    this->x = x;
    this->y = y;
}

std::ostream& operator<<(std::ostream& os, const Cell& cell) {
    os <<  "x: " << cell.getX() << ", " << "y: " << cell.getY();
    return os;
}