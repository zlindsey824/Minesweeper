#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "board.h"

#define BASE 48


Board::Board(int size, int mines):
boardSize(size),
numOfMines(mines)
{
	gameBoard =new char*[boardSize];
	playBoard = new char*[boardSize];
	for (int i = 0; i < boardSize; i++)
	{
		gameBoard[i] = new char[boardSize];
		playBoard[i] = new char[boardSize];
	}
	setup();
}

void Board::display(){
	std::cout << '+';
	for (int j = 0; j < boardSize; j++){
		std::cout << '-' << '+';
	}
	std::cout << std::endl;
	for (int i = 0; i < boardSize; i++){
		std::cout << '|';
		for (int j = 0; j < boardSize; j++){
			std::cout << playBoard[i][j] << '|';
		}
		std::cout << std::endl;
		std::cout << '+';
		for (int j = 0; j < boardSize; j++){
			std::cout << '-' << '+';
		}
		std::cout << std::endl;
	}
}

bool Board::checkTile(int row, int col){
	if (row < 0 || row >= boardSize || col < 0 || col >= boardSize)
		return 1;

	if (gameBoard[row][col] != '0'){
		if (gameBoard[row][col] == 'X'){
			if (first){
				int r = 0, c = 0;
				while (gameBoard[r][c] == 'X'){
					c++;
					if (c >= boardSize){
						r++;
						c = 0;
					}
				}
				gameBoard[r][c] = gameBoard[row][col];
				gameBoard[row][col] = ' ';
				countMines();
			}
			else{
				revealMines();
				return 0;
			}
		}
		playBoard[row][col] = gameBoard[row][col];
		return 1;
	}
	checkTile(row-1, col-1);
	checkTile(row-1, col);
	checkTile(row-1, col+1);
	checkTile(row, col+1);
	checkTile(row+1, col+1);
	checkTile(row+1, col);
	checkTile(row+1, col-1);
	checkTile(row, col-1);
}

bool Board::flagTile(int row, int col){
	if (playBoard[row][col] == ' ' || playBoard[row][col] == '!'){
		playBoard[row][col] = (playBoard[row][col] == ' ') ? '!' : ' ';
		return 1;
	}
	return 0;
}

void Board::setup(){
	for (int i = 0; i < boardSize; i++){
		for (int j = 0; j < boardSize; j++){
			gameBoard[i][j] = ' ';
			playBoard[i][j] = ' ';
		}
	}
	addMines();
	countMines();
}

void Board::addMines(){
	srand(time(NULL));
	int b = 0;
	while ( b < numOfMines ){
		int row = rand()%boardSize;
		int col = rand()%boardSize;
		if (gameBoard[row][col] == ' '){
			gameBoard[row][col] = 'X';
			b++;
		}
	}
}

void Board::countMines(){
	int count;
	for (int i = 0; i < boardSize; i++){
		for (int j = 0; j < boardSize; j++){
			count = 0;
			if (gameBoard[i][j] != 'X'){
				//Upper Left
				if (i != 0 && j != 0)
					if (gameBoard[i-1][j-1] == 'X') count++;
				//Upper Middle
				if (i != 0)
					if (gameBoard[i-1][j] == 'X') count++;
				//Upper Right
				if (i != 0 && j != boardSize-1)
					if (gameBoard[i-1][j+1] == 'X') count++;
				//Mid Right
				if (j != boardSize-1)
					if (gameBoard[i][j+1] == 'X') count++;
				//Lower Right
				if (j != boardSize-1 && i != boardSize-1)
					if (gameBoard[i+1][j+1] == 'X') count++;
				//Lower Middle
				if (i != boardSize-1)
					if (gameBoard[i+1][j] == 'X') count++;
				//Lower Left
				if (i != boardSize-1 && j != 0)
					if (gameBoard[i+1][j-1] == 'X') count++;
				//Mid Left
				if (j != 0)
					if (gameBoard[i][j-1] == 'X') count++;

				//itoa(count,gameBoard[i][j],10);
				gameBoard[i][j] = BASE + count;
			}
		}
	}
}

void Board::revealMines(){
	for (int i = 0; i < boardSize; i++){
		for (int j = 0; j < boardSize; j++){
			if (gameBoard[i][j] == 'X')
				playBoard[i][j] = gameBoard[i][j];
		}
	}
}
