#include "Worm.hpp"

Worm::Worm(Cell headLocation, int numRows, int numColumns) {
    queue.resize((numRows - 1) * (numColumns - 1), nullptr);
    addHead(headLocation);
    head = 1;
    tail = 0;
}

void Worm::addHead(Cell location) {
    if (queue.empty()) {
        std::cout << "ERROR: Trying to add a head when the vector is empty";
    }
    // Adds the head at the next spot. If the increment needs to wrap around to beginning, do it
    queue.at(head++) = new Cell(location);
    head %= queue.size(); 
}

void Worm::removeTail() {
    if (queue.empty()) {
        std::cout << "ERROR: Trying to remove the tail when the vector is empty";
    }
    // Removes the tail and increment. Wrap to the beginning as needed.
    queue.at(tail++) = nullptr;
    tail %= queue.size();
}

void Worm::print() {
    std::cout << "Worm:" << std::endl;
    std::cout << "Head: " << head << ", Tail: " << tail << std::endl; 
    int vectorIndex = 0;
    for (const Cell* c : queue) {
        if (c != nullptr) {
            std::cout << "Vector Index: " << vectorIndex++ << ", " << *c << std::endl;
        } else {
            std::cout << "Vector Index: " << vectorIndex++ << ", empty" << std::endl;
        }
    }
    std::cout << "------------------------" << std::endl;
}

Cell* Worm::getHead() {
    if (queue.size() <= 0) {
        std::cout << "Snake queue size should not be zero or less than zero!!"
            << " Size: " << queue.size() << std::endl;
        exit(0);
    }

    int headIndex = (head == 0) ? queue.size() - 1 : head - 1;
    return queue.at(headIndex);
}

Cell* Worm::getTail() {
    if (queue.size() <= 0) {
        std::cout << "Snake queue size should not be zero or less than zero!!"
            << " Size: " << queue.size() << std::endl;
        exit(0);
    }

    return queue.at(tail);
}

void Worm::renderWorm(Board &board) {
    // Render head
    int headIndex = (head == 0) ? queue.size() - 1 : head - 1;
    Cell* headCell = queue.at(headIndex);
    board.writeBoard(headCell->getY(), headCell->getX(), '@');

    // Render tail
    int index = tail;
    int headCheck = head - 1;
    while (index != headCheck) {
        Cell* tailCell = queue.at(index);
        if (tailCell == nullptr) {
            std::cout << "ERROR: nullptr" << std::endl;
            std::cout << "index: " << index << std::endl;
            std::cout << "head: " << head << std::endl;
        }
        board.writeBoard(tailCell->getY(), tailCell->getX(), 'o');

        index++;
        index %= queue.size();

        headCheck = head - 1;
        if (headCheck < 0) {
            headCheck = queue.size() - 1;
        }
    }
}