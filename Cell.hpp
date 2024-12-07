#ifndef CELL_H
#define CELL_H

class Cell {
public:
    Cell();
    Cell(int x, int y);
    int getX() const { return x; }
    int getY() const { return y; }
    friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
private:
    int x;
    int y;
};

#endif