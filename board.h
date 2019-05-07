#ifndef BOARD_H
#define BOARD_H

class Board{
public:
	Board(int size, int bombs);
	void display();
	
private:
	void setup();
	void addBombs();
	void countBombs();

	int boardSize;
	int numOfBombs;
	char** gameBoard;
};

#endif
