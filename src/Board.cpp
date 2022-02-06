#include "Board.h"

#include <iostream>
#include <sstream>


Board::Board(const std::string& data) {
	this->set(data);
}

// Sets the board data
void Board::set(const std::string& data) {
	// Checking the data size
	if (data.size() != 81) {
		printf("Board data input has to be of size 81!");
		std::cin.get();
		exit(1);
	}

	// Saving the data
	int emptyCount = 0;
	for (int i = 0; i < 81; i++) {
		if (data[i] > 47 && data[i] < 58) {
			this->data[i] = data[i] - 48;
		}
		else {
			this->data[i] = 0;
			emptyCount++;
		}
	}
	this->emptyCount = emptyCount;
}

// Returns the data as a string
std::string Board::get() {
	std::stringstream ss;
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			const int i = y * 9 + x;
			if (this->data[i] == 0) {
				ss << ' ';
			}
			else {
				ss << char(this->data[i] + 48);
			}
			ss << ' ';
		}
		ss << '\n';
	}
	return ss.str();
}

// Returns the empty count
int Board::empty() {
	return this->emptyCount;
}

// Prints the board
void Board::print() {
	std::cout << this->get();
}

// Clears the board
void Board::clear() {
	for (int i = 0; i < 81; i++) {
		this->data[i] = 0;
	}
	this->emptyCount = 81;
}

// Checks if the number is in row
bool Board::isInRow(int y, int num) {
	for (int x = 0; x < 9; x++) {
		if (this->data[y * 9 + x] == num) {
			return true;
		}
	}
	return false;
}

// Checks if the number is in col
bool Board::isInCol(int x, int num) {
	for (int y = 0; y < 9; y++) {
		if (this->data[y * 9 + x] == num) {
			return true;
		}
	}
	return false;
}

// Checks if the number is in square
bool Board::isInSqr(int sqrX, int sqrY, int num) {
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			if (this->data[(sqrX * 3 + sqrY * 27) + y * 9 + x] == num) {
				return true;
			}
		}
	}
	return false;
}

// Returns the possible square spots for the given number
int Board::availSqrCells(int sqrX, int sqrY, int num) {
	int n = 0;
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			// Getting the index
			const int i = (sqrX * 3 + sqrY * 27) + y * 9 + x;

			// Checking
			if (this->data[i] == 0 && !this->isInRow(sqrY * 3 + y, num) && !this->isInCol(sqrX * 3 + x, num)) {
				n++;
			}
		}
	}
	return n;
}

// Solves the board rows
void Board::solveRows() {
	// Loop through rows
	for (int y = 0; y < 9; y++) {
		// Info
		int rowEmptyCount = 0;
		int nonEmptySum = 0;
		int emptyPos = 0;

		// Loop through x
		for (int x = 0; x < 9; x++) {
			// Getting the index
			const int i = 9 * y + x;

			// Checking if the spot is empty
			if (this->data[i] == 0) {
				rowEmptyCount++;
				emptyPos = i;
			}

			// Else adding to the sum
			else {
				nonEmptySum += this->data[i];
			}

			// Breaking if there is more than 1 empty space
			if (rowEmptyCount > 1) {
				break;
			}
		}

		// Solving if there is only 1 empty space 
		if (rowEmptyCount == 1) {
			this->data[emptyPos] = 45 - nonEmptySum;
			this->emptyCount--;
		}
	}
}

// Solves the board cols
void Board::solveCols() {
	// Loop through cols
	for (int x = 0; x < 9; x++) {
		// Info
		int colEmptyCount = 0;
		int nonEmptySum = 0;
		int emptyPos = 0;

		// Loop through y
		for (int y = 0; y < 9; y++) {
			// Getting the index
			const int i = 9 * y + x;

			// Checking if the spot is empty
			if (this->data[i] == 0) {
				colEmptyCount++;
				emptyPos = i;
			}

			// Else adding to the sum
			else {
				nonEmptySum += this->data[i];
			}

			// Breaking if there is more than 1 empty space
			if (colEmptyCount > 1) {
				break;
			}
		}

		// Solving if there is only 1 empty space
		if (colEmptyCount == 1) {
			this->data[emptyPos] = 45 - nonEmptySum;
			this->emptyCount--;
		}
	}
}

// Solves a square
void Board::solveSquare(int sqrX, int sqrY) {
	// Looping through square y
	for (int y = 0; y < 3; y++) {
		// Looping through square x
		for (int x = 0; x < 3; x++) {
			// Getting the index
			const int ind = (sqrX * 3 + sqrY * 27) + y * 9 + x;

			// Checking if the cell is empty
			if (this->data[ind] == 0) {
				// Looping through possible numbers
				for (int i = 1; i <= 9; i++) {
					// Checking if number already exist in the square, row and column
					if (!this->isInSqr(sqrX, sqrY, i) && !this->isInRow(sqrY * 3 + y, i) && !this->isInCol(sqrX * 3 + x, i)) {
						// Checking if only 1 cell in the square can contain that number
						if (this->availSqrCells(sqrX, sqrY, i) == 1) {
							this->data[ind] = i;
							this->emptyCount--;
							break;
						}
					}
				}
			}
		}
	}
}

// Solves the board
void Board::solve() {
	while (this->emptyCount != 0) {
		// Saving the last empty count
		const int oldEmptyCount = this->emptyCount;

		// Solving the rows
		this->solveRows();
		
		// Solving the cols
		this->solveCols();

		// Solving the squares
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				this->solveSquare(x, y);
			}
		}

		// Checking if no spots were solved
		if (this->emptyCount == oldEmptyCount) {
			break;
		}
	}
}
