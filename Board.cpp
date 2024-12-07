#include "Board.hpp"

void Board::writeWalls() {
    char wall = '*';
    int rowSize = board.size();
    int columnSize = board.at(0).size();

    // Top row
    for (int i = 0; i < rowSize; i++) {
        board.at(0).at(i) = wall;
    }

    // Walls
    for (int i = 1; i < columnSize; i++) {
        board.at(i).at(0) = wall;
        board.at(i).at(columnSize - 1) = wall;
    }

    // Bottom row
    for (int i = 0; i < rowSize; i++) {
        board.at(rowSize - 1).at(i) = wall;
    }
}

void Board::renderBoard() {
     for (auto row : board) {
          for (char c : row) {
               std::cout << c << " ";
          }
          std::cout << std::endl;
     }
}

void Board::clearBoard() {
    for (int row = 0; row < board.size(); row++) {
        for (int column = 0; column < board.at(0).size(); column++) {
            board.at(row).at(column) = ' ';
        }
    }
}

void Board::writeBoard(int row, int column, char c) {
    if (row < 1 || row > board.size() - 1 || column < 1 || column > board.at(0).size() - 1) {
        std::cout << "OOB write to board: Row: " << row  << ", Column: " << column << std::endl;
        exit(1);
    }

    board.at(row).at(column) = c;
}