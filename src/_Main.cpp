#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "Board.h"


int main() {
	Board board = Board("//46789///3/////5/2///5///15//4/6//99//3/7//43/2///8/641/////92/9/////6///57193//");
	board.print();

	std::cout << std::endl;

	board.solve();
	board.print();


	std::cin.get();
}
