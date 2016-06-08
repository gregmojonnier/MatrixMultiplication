#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <stdexcept>
#include <chrono>
#include "../src/Matrix.h"
 
using namespace std;
using ::testing::Eq;
using ::testing::Lt;

TEST(Matrix, MustBeInitializedWithRowAndColumnSize) { 
	Matrix m({3,4});

	ASSERT_THAT(m.rows(), Eq(3));
	ASSERT_THAT(m.columns(), Eq(4));
}

TEST(Matrix, ThrowsInvalidArgumentWhenStartingRowOrColumnAreLessThanOne) { 
	ASSERT_THROW(Matrix({-3,-4}), invalid_argument);
}

TEST(Matrix, ValuesStartAsZeroByDefault) { 
	Matrix m({1,1});

	ASSERT_THAT(m.get_value({0,0}), Eq(0));
}

TEST(Matrix, StartValuesCanBeSetThroughConstructor) { 
	Matrix m({1,1}, 9);

	ASSERT_THAT(m.get_value({0,0}), Eq(9));
}

TEST(Matrix_get_value, CanBeUsedToRetrieveIndividualCellValues) { 
	Matrix m({2,1});
	m.set_value({1, 0}, 33);

	int value = m.get_value({1, 0});

	ASSERT_THAT(value, Eq(33));
}

TEST(Matrix_get_value, ThrowsInvalidArgumentWhenGivenCellNotInMatrix) { 
	Matrix m({1,1}); // only valid cell is {0, 0}

	ASSERT_THROW(m.get_value({-1, 0}), invalid_argument);
	ASSERT_THROW(m.get_value({0, -1}), invalid_argument);
	ASSERT_THROW(m.get_value({1, 0}), invalid_argument);
	ASSERT_THROW(m.get_value({0, 1}), invalid_argument);
}

TEST(Matrix_set_value, CanBeUsedToSetIndividualCellValues) { 
	Matrix m({1,1});
	
	m.set_value({0, 0}, 9);

	ASSERT_THAT(m.get_value({0, 0}), Eq(9));
}

TEST(Matrix_set_value, ThrowsInvalidArgumentWhenGivenCellNotInMatrix) { 
	Matrix m({1,1}); // only valid cell is {0, 0}

	ASSERT_THROW(m.set_value({-1, 0}, 2), invalid_argument);
	ASSERT_THROW(m.set_value({0, -1}, 2), invalid_argument);
	ASSERT_THROW(m.set_value({1, 0}, 2), invalid_argument);
	ASSERT_THROW(m.set_value({0, 1}, 2), invalid_argument);
}

TEST(Matrix_sum, AnswersWithCorrectSumWhenAsked) { 
	Matrix oneCellMatrix({1,1}, 2); 
	Matrix fourCellMatrix({2,2}, 2); 

	int oneCellSum = oneCellMatrix.sum();
	int fourCellSum = fourCellMatrix.sum();

	ASSERT_THAT(oneCellSum, Eq(2));
	ASSERT_THAT(fourCellSum, Eq(8));
}

TEST(AMatrix, MutipliedByAnotherResultsInANewOne) {
	Matrix m1({1,1}, 3); // [3]
	Matrix m2({1,1}, 7); // [7]

	Matrix m3 = m1 * m2;

	ASSERT_THAT(m3.get_value({0,0}), Eq(21));
}

TEST(AMatrix, ThrowsInvalidArgumentWhenAskedToMultiplyMatricesWithMismatchedInnerDimensions) {
	// to be able to multiply 2 matrices, matrix 1's column count must match matrix 2's row count
	Matrix m1({1,4}, 3);
	Matrix m2({2,1}, 7);

	ASSERT_THROW(m1 * m2, invalid_argument);
}

TEST(AMatrix, MutipliesSmallMatricesCorrectly) {
	Matrix m1({2,1}, 2);
	Matrix m2({1,2}, 2);

	Matrix m3 = m1 * m2; // [2]  *  [2 2]
						 // [2]     

								   // Expected
	ASSERT_THAT(m3.sum(), Eq(16)); // [4 4]
								   // [4 4]
}

TEST(AMatrix, MutipliesMediumMatricesCorrectly) {
	Matrix m1({2,2}, 2);
	Matrix m2({2,2}, 2);

	Matrix m3 = m1 * m2; // [2 2]  *  [2 2]
						 // [2 2]     [2 2]

								   // Expected
	ASSERT_THAT(m3.sum(), Eq(32)); // [8 8]
								   // [8 8]
}

TEST(AMatrix, MutipliesLargeMatricesCorrectly) {
	int rows=600, columns=600, cellValue=11;
	int eachCellValue = ((cellValue*cellValue) * rows), totalCells = (rows * columns);
	Matrix m1({rows,columns}, cellValue);
	Matrix m2({rows,columns}, cellValue);

	Matrix m3 = m1 * m2;

	int expectedSum = eachCellValue * totalCells;
	ASSERT_THAT(m3.sum(), Eq(expectedSum));
}

TEST(AMatrix, MutipliesMassiveMatricesInATimelyManner) {
	// (600x600) with value of 11, takes roughly 8200 ms(single threaded), UNACCEPTABLE!
	// Threaded solution dropped time down to roughly 3300 ms :D
	int rows=600, columns=600, cellValue=11;
	Matrix m1({rows,columns}, cellValue);
	Matrix m2({rows,columns}, cellValue);

	auto start = chrono::steady_clock::now();
	Matrix m3 = m1 * m2;
	auto end = chrono::steady_clock::now();
	double duration = chrono::duration<double, milli>(end - start).count();

	ASSERT_THAT(duration, Lt(4100));
}
