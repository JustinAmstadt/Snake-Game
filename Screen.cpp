#include <iomanip>
#include <random>

#include "Screen.hpp"
#include "Board.hpp"

Screen::Screen(int rowSize, int columnSize) {

    // Bounds checking
    if (rowSize < 9 || rowSize > 25) {
        std::cout << "Enter in a valid size between 9 and 25 inclusive" << std::endl;
        exit(1);
    }
    if (columnSize < 9 || columnSize > 80) {
        std::cout << "Enter in a valid size between 9 and 80 inclusive" << std::endl;
        exit(1);
    }

    this->rowSize = rowSize;
    this->columnSize = columnSize;

    // Init FreePool
    int index = 0;
    for (int i = 1; i < columnSize; i++) {
        for (int j = 1; j < rowSize; j++) {
            freePool.push_back(Cell(j, i));
            index++;
        }
    }
    fpLastIndex = index;

    // Init screen vector

    // Set up first wall
    std::vector<int> wall(rowSize + 1, -1);
    screen.push_back(wall);

    for (int i = 0; i < columnSize - 1; i++) {
        std::vector<int> row;
        row.push_back(-1); // Add left side wall
        for (int j = 0; j < rowSize - 1; j++) {
            int cellNum = getCellNum(i, j);
            row.push_back(cellNum);
        }
        row.push_back(-1); // Add right side wall
        screen.push_back(row);

    }

    // Set up last wall
    screen.push_back(wall);
}

int Screen::getCellNum(int row, int column) {
    return row * (rowSize - 1) + column;
}

void Screen::printScreen() {
    // Print out Free Pool;
    std::cout << "FreePool:" << std::endl;
    std::cout << "Last Index: " << fpLastIndex << std::endl;
    int index = 0;
    for (const Cell c : freePool) {
        std::cout << index++ << ": " << c << std::endl;
    }
    std::cout << "------------------------" << std::endl;

    // Print out 2D screen
    std::cout << "Screen: " << std::endl;
    for (int i = 0; i < screen.size(); i++) {
        for (int j = 0; j < screen.at(0).size(); j++) {
            std::cout << std::setw(4) << screen.at(i).at(j);
        }
        std::cout << std::endl;
    }

    std::cout << "------------------------" << std::endl;
}

// Ensures that the spot isn't a wall or a worm part
bool Screen::isFree(int x, int y) {
    return screen.at(y).at(x) != -1;
}

bool Screen::makeOccupied(Cell c) {
    return makeOccupied(c.getX(), c.getY());
}

int Screen::isMunchie(int x, int y) {
    // std::cout << "munchie location: x: " << munchieLocation.getX() << ", y: " << munchieLocation.getY() << std::endl;
    // std::cout << "new postion: x: " << x << ", y: " << y << std::endl;
    if (x == munchieLocation.getX() && y == munchieLocation.getY()) {
        return munchieValue;
    }

    return 0;
}

bool Screen::makeOccupied(int x, int y) {
    if (!isFree(x, y)) {
        // std::cout << "ERROR: Tried to called makeOccupied when the spot was already occupied!" << std::endl;
        return false;
    }

    // Set tile on the screen to -1
    int fpIndex = screen.at(y).at(x);
    screen.at(y).at(x) = -1;

    // Remove the element from the Free Pool and replace it with the last element
    // then, reduce the fpLastIndex by 1
    freePool.at(fpIndex) = freePool.at(fpLastIndex - 1);
    fpLastIndex--;

    // Update the reference in the screen to point to the correct index in the Free Pool
    // If the last reference is the spot it needs to move to, don't update
    Cell lastCell = freePool.at(fpIndex);
    if (!(x == lastCell.getX() && y == lastCell.getY())) {
        screen.at(lastCell.getY()).at(lastCell.getX()) = fpIndex;
    }
    
    return true;
}

void Screen::makeFree(int x, int y) {
    if (isFree(x, y)) {
        std::cout << "ERROR: Tried to called makeFree when the spot was already free!" << std::endl;
        exit(1);
    }

    // Add one to length of free pool
    fpLastIndex++;

    // Free screen and give it it's reference value in the Free Pool
    screen.at(y).at(x) = fpLastIndex - 1;

    // Add spot to the end of Free Pool
    freePool.at(fpLastIndex - 1) = Cell(x, y);
}

int Screen::chooseARandomFreeCell() {
    int maxValue = fpLastIndex - 1;
    return std::rand() % (maxValue + 1);
}

void Screen::makeMunchie() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 9); // Choose between 1 - 9

    munchieValue = dis(gen);

    int munchieFpIndex = chooseARandomFreeCell();
    munchieLocation = freePool[munchieFpIndex];

    makeOccupied(munchieLocation);
}

void Screen::correctnessReport() {
    for (int i = 1; i < screen.size(); i++) {
        for (int j = 1; j < screen[0].size(); j++) {
            int fpIndex = screen.at(i).at(j);
            if (fpIndex != -1) {
                Cell c = freePool.at(fpIndex);
                if (c.getX() != j || c.getY() != i) {
                    std::cout << "Discrepancy between the Free Pool and the Screen: " << std::endl;
                    std::cout << "Screen Coords: Row: " << i << ", Column: " << j << std::endl;
                    std::cout << "Coords in Free Pool at index " << fpIndex << ": " <<
                        "Row: " << c.getY() << ", Column: " << c.getX() << std::endl;
                }
            }
        }
    }
}

int Screen::getRowSize() {
    return rowSize;
}

int Screen::getColumnSize() {
    return columnSize;
}

void Screen::renderMunchie(Board &board) {
    char ch = '0' + munchieValue;
    board.writeBoard(munchieLocation.getY(), munchieLocation.getX(), ch);
    // std::cout << "Munchie pos: row: " << munchieLocation.getY() << " column: " << munchieLocation.getX() << std::endl;
}