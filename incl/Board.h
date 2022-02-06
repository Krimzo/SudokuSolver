#pragma once

#include <string>


class Board {
private:
	int data[81];
	int emptyCount;

	bool isInRow(int, int);
	bool isInCol(int, int);
	bool isInSqr(int, int, int);

	int availSqrCells(int, int, int);

	void solveRows();
	void solveCols();
	void solveSquare(int, int);

public:
	Board(const std::string&);

	void set(const std::string&);

	std::string get();
	int empty();

	void print();

	void clear();

	void solve();
};
