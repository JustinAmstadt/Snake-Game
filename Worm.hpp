#ifndef WORM_H
#define WORM_H

#include <vector>
#include <iostream>

#include "Cell.hpp"
#include "Board.hpp"

class Worm {
public:
    Worm(Cell headLocation, int numRows, int numColumns);
    void removeTail();
    Cell* getHead();
    Cell* getTail();
    void addHead(Cell location);
    void print();
    void renderWorm(Board &board);

private:
    std::vector<Cell*> queue;
    int head;
    int tail;

};

#endif