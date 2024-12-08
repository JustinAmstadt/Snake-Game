#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include <iostream>

#include "Cell.hpp"
#include "Board.hpp"

// Avoid circular dependency issue
class Board;

class Screen {
public:
    Screen(int rowSize, int columnSize);
    void makeFree(int x, int y);
    bool isFree(int x, int y);
    bool makeOccupied(int x, int y);
    bool makeOccupied(Cell c);
    void makeMunchie();
    int isMunchie(int x, int y);

    int getRowSize();
    int getColumnSize();

    void renderMunchie(Board &board);

    void printScreen();
    void correctnessReport();

private:
    std::vector<std::vector<int> > screen;
    std::vector<Cell> freePool;
    Cell munchieLocation;
    int munchieValue;
    int fpLastIndex;
    int rowSize;
    int columnSize;

    int chooseARandomFreeCell();
    int getCellNum(int row, int column);
};

#endif