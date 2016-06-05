#include "Matrix.h"
#include <stdexcept>
#include <algorithm>
 
using namespace std;

Matrix::Matrix(int rows, int columns, int start_value) : rows_(rows), columns_(columns)
{
	if (rows < 1 || columns < 1)
		throw invalid_argument("Starting row and column dimensions must be greater than 1!");
	matrix_.resize(rows);
	for (int i = 0; i < rows; ++i)
	{
		matrix_[i].assign(columns, start_value);
	}
}
int Matrix::rows() const noexcept
{
	return rows_;
}

int Matrix::columns() const noexcept
{
	return columns_;
}

int Matrix::get_value(pair<int, int> cell) const
{
	auto& row = cell.first;
	auto& column = cell.second;
	verify_cell_validity(row, column);

	return matrix_[row][column];
}

void Matrix::set_value(pair<int, int> cell, int value)
{
	auto& row = cell.first;
	auto& column = cell.second;
	verify_cell_validity(row, column);

	matrix_[row][column] = value;
}

int Matrix::sum() const noexcept
{
	int sum = 0;
	for (auto& row : matrix_)
	{
		sum = accumulate(row.begin(), row.end(), sum);
	}
	return sum;
}

void Matrix::verify_cell_validity(int row, int column) const
{
	if (row < 0 || column < 0 || row >= rows_ || column >= columns_)
		throw invalid_argument("Cell must be between 0 and rows/columns of matrix. [" + to_string(row) + "," + to_string(column) + "]" );
}
