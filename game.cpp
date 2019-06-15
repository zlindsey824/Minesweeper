#include <iostream>
#include "board.h"



int main(){
	
	std::cout << "Welcome to the game of Minesweeper!" << std::endl;
	std::cout << "Choose a difficulty or select custom." << std::endl;
	std::cout << "b - Beginner" << std::endl;
	std::cout << "i - Intermediate" << std::endl;
	std::cout << "a - Advanced" << std::endl;
	std::cout << "c - Custom" << std::endl;
	
	char mode;
	
	std::cin >> mode;
	
	while (mode != 'b' && mode != 'i' && mode != 'a' && mode != 'c'){
		std::cout << "Please select a difficulty level by typing b, i, a, or c." << std::endl;
		std::cout << "b - Beginner" << std::endl;
		std::cout << "i - Intermediate" << std::endl;
		std::cout << "a - Advanced" << std::endl;
		std::cout << "c - Custom" << std::endl;
		std::cin >> mode;
	}
	
	int size;
	int mines;
	
	if (mode == 'b'){
		size = 8;
		mines = 10;
	} else if (mode == 'i'){
		size = 16;
		mines = 40;
	} else if (mode == 'a'){
		size = 24;
		mines = 99;
	} else if (mode == 'c'){
		std::cout << "You've selected custom." << std::endl;
		std::cout << "Please input a size and amount of mines for the board." << std::endl;
		//Custom size
		std::cout << "The size must be between 8 and 24." << std::endl;
		std::cin >> size;
		if (size < 8){
			size = 8;
			std::cout << "Size auto-set to minimum size of 8" << std::endl;
		} else if (size > 24){
			size = 24;
			std::cout << "Size auto-set to maximum size of 24" << std::endl;
		}
		//Custom mines
		int maxMines = (size*size) - 2;
		std::cout << "The amount of mines must be between 2 and " << maxMines << "." << std::endl;
		std::cin >> mines;
		if (size < 2){
			size = 2;
			std::cout << "Amount of mines auto-set to minimum amount of 2" << std::endl;
		} else if (size > maxMines){
			size = maxMines;
			std::cout << "Amount of mines auto-set to maximum amount of " << maxMines << std::endl;
		}
	}
	
	Board game(size,mines);
	char type;
	int row,column;
	int end = 0;
	std::cout << "Welcome to the game of Minesweeper!" << std::endl;

	while (!end){
		game.display();
		if (!first){
			std::cout << "Would you like to (c)heck or (f)lag a tile?" << std::endl;
			std::cin >> type;
		}
		else
			type = 'c';
		if (type == 'c' || type == 'f'){
			std::cout << "Enter a row and a column (or enter -1 to quit)." << std::endl;
			std::cout << "Row: ";
			std::cin >> row;
			std::cout << "Column: ";
			std::cin >> column;
			if (row < 0 || column < 0)
				end = true;
			else{
				if (type == 'c')
					end = game.checkTile(row, column);
				else if (type == 'f')
					game.flagTile(row, column);

				if (end) game.display();
				if (first) first = false;
			}
		}
	}

	return 0;
}
