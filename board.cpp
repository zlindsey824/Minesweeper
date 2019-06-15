#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "board.h"

#define BASE 48


Board::Board(int size, int mines):
boardSize(size),
numOfMines(mines),
numOfFlags(0)
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
	std::cout << "checking tile" << std::endl;
	if (playBoard[row][col] != ' '
			|| col < 0 || col >= boardSize
			|| row < 0 || row >= boardSize){
		std::cout << "Return" << std::endl;
		return 0;
	}
		std::cout << row << " " << col << std::endl;
	if (gameBoard[row][col] != '0'){
		if (gameBoard[row][col] == 'X'){
			std::cout << row << " " << col << " " << gameBoard[row][col] << std::endl;
			// Allows a free first play that relocates mine to top left corner
			if (first){
				int r = 0, c = 0;
				std::cout << "checking for X" << std::endl;
				while (gameBoard[r][c] == 'X'){
					std::cout << r << " " << c << std::endl;
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
			// Otherwise, end game if mine is clicked
			else{
				revealMines();
				return 1;
			}

		}
		std::cout << row << " " << col << " " << gameBoard[row][col] << std::endl;
		playBoard[row][col] = gameBoard[row][col];
		first = false;
		return checkForWin();
	}
	else{
		std::cout << row << " " << col << " " << gameBoard[row][col] << std::endl;
		playBoard[row][col] = gameBoard[row][col];
		first = false;
	}
	std::cout << "Checking UL" << std::endl;
	checkTile(row-1, col-1);
	std::cout << "Checking UM" << std::endl;
	checkTile(row-1, col);
	std::cout << "Checking UR" << std::endl;
	checkTile(row-1, col+1);
	std::cout << "Checking MR" << std::endl;
	checkTile(row, col+1);
	std::cout << "Checking LR" << std::endl;
	//checkTile(row+1, col+1);
	std::cout << "Checking LM" << std::endl;
	checkTile(row+1, col);
	std::cout << "Checking LL" << std::endl;
	checkTile(row+1, col-1);
	std::cout << "Checking ML" << std::endl;
	checkTile(row, col-1);
	return 0;
}

bool Board::flagTile(int row, int col){
	if ((numOfFlags <= numOfMines) &&
			playBoard[row][col] == ' ' || playBoard[row][col] == '!'){
		playBoard[row][col] = (playBoard[row][col] == ' ') ? '!' : ' ';
		if (playBoard[row][col] == '!' && numOfFlags < numOfMines)
			numOfFlags += 1;
		else
			numOfFlags -= 1;
		return 1;
	}
	return 0;
}

bool Board::checkForWin(){
	for (int row = 0; row < boardSize; row++){
		for (int col = 0; col < boardSize; col++){
			if (playBoard[row][col] == ' ' || playBoard[row][col] == '!'){
				if (gameBoard[row][col] != 'X')
					return 0;
			}
		}
	}
	return 1;
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
