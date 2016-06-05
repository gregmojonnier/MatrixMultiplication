#include "Matrix.h"
#include <stdexcept>
#include <algorithm>
 
using namespace std;

Matrix::Matrix(pair<int, int> dimensions, int start_value)
{
	auto& rows = dimensions.first;
	auto& columns = dimensions.second;

	if (rows < 1 || columns < 1)
		throw invalid_argument("Starting row and column dimensions must be greater than 1!");

	rows_ = rows;
	columns_ = columns;
	matrix_.resize(rows);
	for (int i = 0; i < rows; ++i)
	{
		matrix_[i].assign(columns, start_value);
	}
}

Matrix::~Matrix()
{
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

Matrix Matrix::operator*(const Matrix&rhs)
{
	if (columns_ != rhs.rows())
		throw invalid_argument("Number of columns in the 1st matrix(" + to_string(columns_)
								+ ") should equal the number of rows in the 2nd matrix("
								+ to_string(rhs.rows()) + ") in order to multiply them together.");

	Matrix result({rows_, rhs.columns()});

	for (int row = 0; row < rows_; ++row)
	{
			for (int column = 0; column < rhs.columns(); ++column)
			{
					int cellValue = 0;
					for (int myColumnIdx = 0; myColumnIdx < columns_; ++myColumnIdx)
					{
						int subValue = matrix_[row][myColumnIdx] * rhs.get_value({myColumnIdx, column});
						cellValue += subValue;
					}
					result.set_value({row, column}, cellValue);
			}
	}

	return result;
}

void Matrix::verify_cell_validity(int row, int column) const
{
	if (row < 0 || column < 0 || row >= rows_ || column >= columns_)
		throw invalid_argument("Cell must be between 0 and rows/columns of matrix. [" + to_string(row) + "," + to_string(column) + "]" );
}
