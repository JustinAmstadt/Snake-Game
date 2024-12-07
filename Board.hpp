#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>

#include "Screen.hpp"

class Board {
public:
    Board(int numRows, int numColumns) {
        this->board = std::vector<std::vector<char> >(numRows + 1, std::vector<char>(numColumns + 1, ' '));
    }

    void writeWalls();
    void clearBoard();
    void renderBoard();
    void writeBoard(int row, int column, char c);
private:
    std::vector<std::vector<char> > board;
};

#endif