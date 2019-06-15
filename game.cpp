#include <iostream>
#include "board.h"



int main(){

	Board game(3,2);
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
