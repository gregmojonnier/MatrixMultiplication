#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <stdexcept>
#include "../src/Matrix.h"
 
using namespace std;
using ::testing::Eq;

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

TEST(AMatrix, MutipliesCorrectlyASimpleExample) {
	Matrix m1({2,1}, 2);
	Matrix m2({1,2}, 2);

	Matrix m3 = m1 * m2; // [2]  *  [2 2]
						 // [2]     

								   // Expected
	ASSERT_THAT(m3.sum(), Eq(16)); // [4 4]
								   // [4 4]
}

TEST(AMatrix, MutipliesCorrectlyAMoreComplexExample) {
	Matrix m1({2,2}, 2);
	Matrix m2({2,2}, 2);

	Matrix m3 = m1 * m2; // [2 2]  *  [2 2]
						 // [2 2]     [2 2]

								   // Expected
	ASSERT_THAT(m3.sum(), Eq(32)); // [8 8]
								   // [8 8]
}
