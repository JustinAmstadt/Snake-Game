#include <iostream>
#include <string>
#include <vector>

#include "Worm.hpp"
#include "Screen.hpp"
#include "Cell.hpp"
#include "Board.hpp"

void startup( void );
void terminate( void );

// TODO Free the tail first
bool move(Screen* screen, Worm* worm, int x, int y, int& munchieValue) {
     static int newTailCount = 0;

     int newX = worm->getHead()->getX() + x;
     int newY = worm->getHead()->getY() + y;

     // Do munchie check
     munchieValue = screen->isMunchie(newX, newY);
     newTailCount += munchieValue;

     // std::cout << "munchie value: " << munchieValue << std::endl;
     if (munchieValue > 0) {
          screen->makeFree(newX, newY);
          screen->makeMunchie();
     }

     if (newTailCount > 0) {
          // Keep the old tail, but reduce the counter
          newTailCount--;
     } else {
          // Free the leftover tail
          screen->makeFree(worm->getTail()->getX(), worm->getTail()->getY());
          worm->removeTail();
     }

     // Move the worm on the screen and in the worm vector
     worm->addHead(Cell(newX, newY));
     return screen->makeOccupied(newX, newY);
}


void renderHeader(int score) {
     std::cout << "Score: " << score << std::endl;
}

int main(int argc, char *argv[])
{
     int numRows = 0;
     int numColumns = 0;

     if (argc == 1) {
          numRows = 9;
          numColumns = 9;
     } else if (argc == 3) {
          numRows = std::stoi(argv[1]);
          numColumns = std::stoi(argv[2]);
     }

     Board board(numRows, numColumns);

     Cell startHeadLocation(numRows / 2, numColumns / 2);

     Worm* worm = new Worm(startHeadLocation, numRows, numColumns);
     Screen* screen = new Screen(numRows, numColumns);
     // Initial head location
     screen->makeOccupied(startHeadLocation.getX(), startHeadLocation.getY());

     screen->makeMunchie();

     int score = 0;

     bool lostFlag = true;
     char input = 'z';
     char lastInput = input;
     while (input != 'x' && lostFlag) {
          int munchieValue = 0;
          // worm->print();
          // screen->printScreen();
          screen->correctnessReport();
          renderHeader(score);
          board.writeWalls();
          screen->renderMunchie(board);
          worm->renderWorm(board);
          board.renderBoard();
          board.clearBoard();

          std::cin >> input;

          switch(input) {
               case 'w':
               case 'k':
                    lostFlag = move(screen, worm, 0, -1, munchieValue);
                    break;
               case 's':
               case 'j':
                    lostFlag = move(screen, worm, 0, 1, munchieValue);
                    break;
               case 'a':
               case 'h':
                    lostFlag = move(screen, worm, -1, 0, munchieValue);
                    break;
               case 'd':
               case 'l':
                    lostFlag = move(screen, worm, 1, 0, munchieValue);
                    break;
               case 'x':
                    break;
          }

          score += munchieValue;
     }
}