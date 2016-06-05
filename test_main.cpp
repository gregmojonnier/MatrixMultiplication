#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <stdexcept>
 
using namespace std;
using ::testing::Eq;

class Matrix {
	public:
		Matrix(int rows, int columns, int start_value=0) : rows_(rows), columns_(columns)
		{
			if (rows < 1 || columns < 1)
				throw std::invalid_argument("Starting row and column dimensions must be greater than 1!");
			matrix_.resize(rows);
			for (int i = 0; i < rows; ++i)
			{
				matrix_[i].assign(columns, start_value);
			}
		}

		int rows() const noexcept
		{
			return rows_;
		}

		int columns() const noexcept
		{
			return columns_;
		}

		int get_value(pair<int, int> cell) const
		{
			auto& row = cell.first;
			auto& column = cell.second;
			if (row < 0 || column < 0 || row >= rows_ || column >= columns_)
				throw std::invalid_argument("Cell must be between 0 and rows/columns of matrix. [" + to_string(row) + "," + to_string(column) + "]" );
			return matrix_[row][column];
		}

		void set_value(pair<int, int> cell, int value)
		{
			auto& row = cell.first;
			auto& column = cell.second;
			if (row < 0 || column < 0 || row >= rows_ || column >= columns_)
				throw std::invalid_argument("Cell must be between 0 and rows/columns of matrix. [" + to_string(row) + "," + to_string(column) + "]" );
			matrix_[row][column] = value;
		}

		int sum() const noexcept
		{
			return 0;
		}

	private:
		vector<vector<int>> matrix_;
		int rows_;
		int columns_;
};

TEST(Matrix, MustBeInitializedWithRowAndColumnSize) { 
	Matrix m(3, 4);

	ASSERT_THAT(m.rows(), Eq(3));
	ASSERT_THAT(m.columns(), Eq(4));
}

TEST(Matrix, ThrowsInvalidArgumentWhenStartingRowOrColumnAreLessThanOne) { 
	ASSERT_THROW(Matrix(-3, -4), invalid_argument);
}

TEST(Matrix, ValuesStartAsZeroByDefault) { 
	Matrix m(1, 1);

	ASSERT_THAT(m.get_value({0,0}), Eq(0));
}

TEST(Matrix, StartValuesCanBeSetThroughConstructor) { 
	Matrix m(1, 1, 9);

	ASSERT_THAT(m.get_value({0,0}), Eq(9));
}

TEST(Matrix_get_value, CanBeUsedToRetrieveIndividualCellValues) { 
	Matrix m(2,1);
	m.set_value({1, 0}, 33);

	int value = m.get_value({1, 0});

	ASSERT_THAT(value, Eq(33));
}

TEST(Matrix_get_value, ThrowsInvalidArgumentWhenGivenCellNotInMatrix) { 
	Matrix m(1,1); // only valid coordinate is {0, 0}

	ASSERT_THROW(m.get_value({-1, 0}), invalid_argument);
	ASSERT_THROW(m.get_value({0, -1}), invalid_argument);
	ASSERT_THROW(m.get_value({1, 0}), invalid_argument);
	ASSERT_THROW(m.get_value({0, 1}), invalid_argument);
}

TEST(Matrix_set_value, CanBeUsedToSetIndividualCellValues) { 
	Matrix m(1,1);
	
	m.set_value({0, 0}, 9);

	ASSERT_THAT(m.get_value({0, 0}), Eq(9));
}

TEST(Matrix_set_value, ThrowsInvalidArgumentWhenGivenCellNotInMatrix) { 
	Matrix m(1,1); // only valid coordinate is {0, 0}

	ASSERT_THROW(m.set_value({-1, 0}, 2), invalid_argument);
	ASSERT_THROW(m.set_value({0, -1}, 2), invalid_argument);
	ASSERT_THROW(m.set_value({1, 0}, 2), invalid_argument);
	ASSERT_THROW(m.set_value({0, 1}, 2), invalid_argument);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
