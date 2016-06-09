#include <utility>
#include <iostream>
#include <vector>

class Matrix {
	public:
		Matrix() = delete;
		Matrix(const std::pair<int, int>& dimensions, int start_value=0);
		virtual ~Matrix();

		int rows() const noexcept;
		int columns() const noexcept;

		int get_value(const std::pair<int, int>& cell) const;
		void set_value(const std::pair<int, int>& cell, int value);

		int sum() const noexcept;
		Matrix operator*(const Matrix& rhs);
	
		friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
	private:
		void verify_cell_validity(int row, int column) const;
		int sum_products_of_matching_cells(int row, int column, const Matrix& rhs) const;

		std::vector<std::vector<int>> matrix_;
		int rows_;
		int columns_;
};
