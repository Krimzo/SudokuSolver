#pragma once

#include <string>


class board
{
	int data_[81] = {};
	int empty_count_ = 81;

	[[nodiscard]] bool is_in_row(int y, int value) const;
	[[nodiscard]] bool is_in_col(int, int) const;
	[[nodiscard]] bool is_in_sqr(int, int, int) const;

	[[nodiscard]] int avail_sqr_cells(int, int, int) const;

	void solve_rows();
	void solve_cols();
	void solve_square(int, int);

public:
	explicit board(const std::string&);

	bool set_values(const std::string&);
	[[nodiscard]] std::string get_values() const;

	void clear();
	[[nodiscard]] int empty_count() const;
	
	void solve();
	void display() const;
};
