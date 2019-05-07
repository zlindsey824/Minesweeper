#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "board.h"

#define BASE 48

Board::Board(int size, int bombs):
boardSize(size),
numOfBombs(bombs)
{
	gameBoard =new char*[boardSize];
	for (int i = 0; i < boardSize; i++)
	{
		gameBoard[i] = new char[boardSize];
	}
	setup();		
}

void Board::display(){
	for (int i = 0; i < boardSize; i++){
		for (int j = 0; j < boardSize; j++){
			std::cout << gameBoard[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

void Board::setup(){
	for (int i = 0; i < boardSize; i++){
		for (int j = 0; j < boardSize; j++){
			gameBoard[i][j] = ' ';
		}
	}
	addBombs();
	countBombs();
}

void Board::addBombs(){
	srand(time(NULL));
	int b = 0;
	while ( b < numOfBombs ){
		int row = rand()%boardSize;
		int col = rand()%boardSize;
		if (gameBoard[row][col] == ' '){
			gameBoard[row][col] = 'X';
			b++;
		}
	}
}

void Board::countBombs(){
	int count;
	for (int i = 0; i < boardSize; i++){
		for (int j = 0; j < boardSize; j++){
			count = 0;
			if (gameBoard[i][j] == ' '){
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
