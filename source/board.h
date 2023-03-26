#pragma once

#include <iostream>
#include <sstream>


class board
{
	int data_[81] = {};
	int empty_count_ = 81;

	bool is_in_row(int y, int value) const;
	bool is_in_col(int x, int value) const;
	bool is_in_sqr(int sqr_x, int sqr_y, int num) const;

	int avail_sqr_cells(int sqr_x, int sqr_y, int value) const;

	void solve_rows();
	void solve_cols();
	void solve_square(int sqr_x, int sqr_y);

public:
	board(const std::string& data);

	bool set_values(const std::string& data);
	std::string get_values() const;

	void clear();
	int empty_count() const;
	
	void solve();
	void display() const;
};
