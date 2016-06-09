#include "Matrix.h"
#include <stdexcept>
#include <algorithm>
#include <thread>
 
using namespace std;

Matrix::Matrix(const pair<int, int>& dimensions, int start_value)
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

int Matrix::get_value(const pair<int, int>& cell) const
{
	auto& row = cell.first;
	auto& column = cell.second;
	verify_cell_validity(row, column);

	return matrix_[row][column];
}

void Matrix::set_value(const pair<int, int>& cell, int value)
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

	calc_product_of_self_and_rhs(rhs, result);

	return result;
}

void Matrix::calc_product_of_self_and_rhs(const Matrix& rhs, Matrix& result) const
{
	int thread_count = (std::thread::hardware_concurrency() > 0) ? std::thread::hardware_concurrency() : 1;
	int work_per_thread = rows_ / thread_count;

	// no sense in using multiple threads when there's not enough work
	if (work_per_thread < 250) {
		thread_count = 1;
	}

	vector<thread> workers;
	// work is divided between threads by result rows
	auto work = [&](int start_row, int end_row) {
			for (int row = start_row; row < end_row; ++row)
			{
					for (int column = 0; column < rhs.columns(); ++column)
					{
							// result vector sizes are set beforehand, threads have no overlap in writing
							result.set_value({row, column}, sum_products_of_matching_cells(row, column, rhs));
					}
			}
	};
	
	int start_row = 0;
	for (int i = 0; i < thread_count; ++i)
	{
		if (i + 1 >= thread_count)
		{
			work(start_row, rows_);
		}
		else
		{
			workers.emplace_back(work, start_row, start_row+work_per_thread);
		}
		start_row += work_per_thread;
	}

	for (auto& worker : workers)
	{
		worker.join();
	}
}

int Matrix::sum_products_of_matching_cells(int row, int column, const Matrix& rhs) const
{
	// Calculates a final cell value in a new matrix resulting from multiplying 2 matrices
	//		The new cell is the sum of the products of matching indexes(multiplicandIdx)
	//		Onus is on caller of function to verify our columns_ and rhs's rows lengths match(requirement of matrix multiplication)
	int cellValue = 0;
	for (int multiplicandIdx = 0; multiplicandIdx < columns_; ++multiplicandIdx)
	{
		cellValue += matrix_[row][multiplicandIdx] * rhs.get_value({multiplicandIdx, column});
	}
	return cellValue;
}

void Matrix::verify_cell_validity(int row, int column) const
{
	if (row < 0 || column < 0 || row >= rows_ || column >= columns_)
		throw invalid_argument("Cell must be between 0 and rows/columns of matrix. [" + to_string(row) + "," + to_string(column) + "]" );
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
	size_t rows = matrix.matrix_.size();
	for (size_t rowIdx = 0; rowIdx < rows; ++rowIdx)
	{
		auto& row = matrix.matrix_[rowIdx];
		size_t columns = row.size();
		for (size_t valueIdx = 0; valueIdx < columns; ++valueIdx)
		{
			os << row[valueIdx];
			if (valueIdx + 1 < columns)
			{
					os << " ";
			}
			else if (rowIdx + 1 < rows)
			{
					os << endl;
			}
		}
	}
    return os;
}
