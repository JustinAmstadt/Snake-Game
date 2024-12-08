#include <iostream>
#include <string>
#include <vector>
#include <random>

#include "Worm.hpp"
#include "Screen.hpp"
#include "Cell.hpp"
#include "Board.hpp"

#define NUM_GAMES 5000

bool move(Screen* screen, Worm* worm, int x, int y, int& munchieValue, int& newTailCount) {
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

char chooseRandomInput() {
    const char directions[] = {'w', 'a', 's', 'd'};
    std::random_device rd; // Random device for seeding
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_int_distribution<> dis(0, 3); // Generate numbers 0 to 3
    return directions[dis(gen)];
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

     int gameCounter = 0;

     while (gameCounter < NUM_GAMES) {
          Board board(numRows, numColumns);

          Cell startHeadLocation(numRows / 2, numColumns / 2);

          Worm* worm = new Worm(startHeadLocation, numRows, numColumns);
          Screen* screen = new Screen(numRows, numColumns);
          // Initial head location
          screen->makeOccupied(startHeadLocation.getX(), startHeadLocation.getY());

          screen->makeMunchie();

          int score = 0;
          int newTailCount = 0;

          bool lostFlag = true;
          char input = 'z';
          char lastInput = input;
          while (input != 'x' && lostFlag) {
               int munchieValue = 0;
               screen->correctnessReport();

               renderHeader(score);
               board.writeWalls();
               screen->renderMunchie(board);
               worm->renderWorm(board);
               board.renderBoard();
               board.clearBoard();

               input = chooseRandomInput();
               std::cout << input << std::endl;

               std::cout << std::endl;

               switch(input) {
                    case 'w':
                    case 'k':
                         lostFlag = move(screen, worm, 0, -1, munchieValue, newTailCount);
                         break;
                    case 's':
                    case 'j':
                         lostFlag = move(screen, worm, 0, 1, munchieValue, newTailCount);
                         break;
                    case 'a':
                    case 'h':
                         lostFlag = move(screen, worm, -1, 0, munchieValue, newTailCount);
                         break;
                    case 'd':
                    case 'l':
                         lostFlag = move(screen, worm, 1, 0, munchieValue, newTailCount);
                         break;
                    case 'x':
                         break;
               }

               score += munchieValue;
          }
          delete worm;
          delete screen;
          gameCounter++;
          std::cout << "-" << std::endl;
     }
}