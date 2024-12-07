
worm.x:  main.o getChar.o Worm.o Board.o Screen.o Cell.o 
	g++ -ggdb -o worm.x main.o getChar.o Worm.o Board.o Screen.o Cell.o -lcurses -ltermcap

main.o: main.cpp
	g++ -c -ggdb main.cpp -o main.o

getChar.o: getChar.cpp 
	gcc -c -ggdb getChar.cpp -o getChar.o

Worm.o: Worm.cpp
	g++ -c -ggdb Worm.cpp -o Worm.o

Screen.o: Screen.cpp
	g++ -c -ggdb Screen.cpp -o Screen.o

Cell.o: Cell.cpp
	g++ -c -ggdb Cell.cpp -o Cell.o

Board.o: Board.cpp
	g++ -c -ggdb Board.cpp -o Board.o

clean:
	/bin/rm -f worm.x main.o getChar.o Worm.o Screen.o FreePool.o Cell.o Board.o *~
