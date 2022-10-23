#include <iostream>
#include "board.h"


int main()
{
	auto board = ::board("//46789///3/////5/2///5///15//4/6//99//3/7//43/2///8/641/////92/9/////6///57193//");
	board.display();

	board.solve();
	board.display();

	std::cin.get();
}
