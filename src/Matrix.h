#include <utility>
#include <iostream>
#include <vector>

class Matrix {
	public:
		Matrix() = delete;
		Matrix(const std::pair<int, int>& dimensions, int start_value=0);
		virtual ~Matrix();

		// getters for matrix info
		int rows() const noexcept;
		int columns() const noexcept;

		// getters/setters for cell values within matrix
		int get_value(const std::pair<int, int>& cell) const;
		void set_value(const std::pair<int, int>& cell, int value);

		// math operations
		int sum() const noexcept;
		Matrix operator*(const Matrix& rhs);
	
		friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
	private:
		void verify_cell_validity(int row, int column) const;
		void calc_product_of_self_and_rhs(const Matrix& rhs, Matrix& result) const;
		int sum_products_of_matching_cells(int row, int column, const Matrix& rhs) const;

		std::vector<std::vector<int>> matrix_;
		int rows_;
		int columns_;
};
