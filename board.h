#ifndef BOARD_H
#define BOARD_H

static bool first = true;

class Board{
public:
	Board(int size, int mines);
	void display();
	bool checkTile(int row, int col);
	bool flagTile(int row, int col);
	bool checkForWin();

private:
	void setup();
	void addMines();
	void countMines();
	void revealMines();

	int boardSize;
	int numOfMines;
	int numOfFlags;
	char** gameBoard;
	char** playBoard;
};

#endif
