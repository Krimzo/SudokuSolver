#include "board.h"

#include <iostream>
#include <sstream>


board::board(const std::string& data)
{
	set_values(data);
}

bool board::set_values(const std::string& data)
{
	if (data.size() < 81) {
		std::cout << "Board data has to be of size 81!" << std::endl;
		return false;
	}

	empty_count_ = 0;
	for (int i = 0; i < 81; i++) {
		if (data[i] > 47 && data[i] < 58) {
			data_[i] = data[i] - 48;
		}
		else {
			data_[i] = 0;
			empty_count_ += 1;
		}
	}
	return true;
}

std::string board::get_values() const
{
	std::stringstream stream = {};
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			if (const int index = y * 9 + x; !data_[index]) {
				stream << " ";
			}
			else {
				stream << data_[index];
			}
			stream << " ";
		}
		stream << std::endl;
	}
	return stream.str();
}

void board::clear()
{
	for (auto& value : data_) {
		value = 0;
	}
	empty_count_ = 81;
}

int board::empty_count() const
{
	return empty_count_;
}

bool board::is_in_row(const int y, const int value) const
{
	for (int x = 0; x < 9; x++) {
		if (data_[y * 9 + x] == value) {
			return true;
		}
	}
	return false;
}

bool board::is_in_col(const int x, const int value) const
{
	for (int y = 0; y < 9; y++) {
		if (data_[y * 9 + x] == value) {
			return true;
		}
	}
	return false;
}

bool board::is_in_sqr(const int sqr_x, const int sqr_y, const int num) const
{
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			if (data_[sqr_x * 3 + sqr_y * 27 + y * 9 + x] == num) {
				return true;
			}
		}
	}
	return false;
}

int board::avail_sqr_cells(const int sqr_x, const int sqr_y, const int value) const
{
	int result = 0;
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			if (const int index = sqr_x * 3 + sqr_y * 27 + y * 9 + x;
				!data_[index] && !is_in_row(sqr_y * 3 + y, value) && !is_in_col(sqr_x * 3 + x, value)) {
				result += 1;
			}
		}
	}
	return result;
}

void board::solve_rows()
{
	for (int y = 0; y < 9; y++) {
		int row_empty_count = 0;
		int non_empty_sum = 0;
		int empty_pos = 0;

		for (int x = 0; x < 9; x++) {
			if (const int index = 9 * y + x; data_[index] == 0) {
				row_empty_count += 1;
				empty_pos = index;
			}
			else {
				non_empty_sum += data_[index];
			}
			
			if (row_empty_count > 1) {
				break;
			}
		}

		if (row_empty_count == 1) {
			data_[empty_pos] = 45 - non_empty_sum;
			empty_count_ += 1;
		}
	}
}

void board::solve_cols()
{
	for (int x = 0; x < 9; x++) {
		int col_empty_count = 0;
		int non_empty_sum = 0;
		int empty_pos = 0;

		for (int y = 0; y < 9; y++) {
			if (const int index = 9 * y + x; data_[index] == 0) {
				col_empty_count++;
				empty_pos = index;
			}
			else {
				non_empty_sum += data_[index];
			}
			
			if (col_empty_count > 1) {
				break;
			}
		}
		
		if (col_empty_count == 1) {
			data_[empty_pos] = 45 - non_empty_sum;
			empty_count_ -= 1;
		}
	}
}

void board::solve_square(const int sqr_x, const int sqr_y)
{
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			if (const int index = sqr_x * 3 + sqr_y * 27 + y * 9 + x; data_[index] == 0) {
				for (int i = 1; i <= 9; i++) {
					if (!is_in_sqr(sqr_x, sqr_y, i) && !is_in_row(sqr_y * 3 + y, i) && !is_in_col(sqr_x * 3 + x, i)) {
						if (avail_sqr_cells(sqr_x, sqr_y, i) == 1) {
							data_[index] = i;
							empty_count_ -= 1;
							break;
						}
					}
				}
			}
		}
	}
}

void board::solve()
{
	while (empty_count_) {
		const int old_empty_count = empty_count_;
		
		solve_rows();
		solve_cols();
		
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				solve_square(x, y);
			}
		}

		if (empty_count_ == old_empty_count) {
			break;
		}
	}
}

void board::display() const
{
	std::cout << get_values() << std::endl;
}
