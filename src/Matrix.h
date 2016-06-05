#include <utility>
#include <vector>

class Matrix {
	public:
		Matrix() = delete;
		Matrix(std::pair<int, int> dimensions, int start_value=0);
		virtual ~Matrix();

		int rows() const noexcept;
		int columns() const noexcept;

		int get_value(std::pair<int, int> cell) const;
		void set_value(std::pair<int, int> cell, int value);

		int sum() const noexcept;
		Matrix operator*(const Matrix&rhs);
	private:
		void verify_cell_validity(int row, int column) const;

		std::vector<std::vector<int>> matrix_;
		int rows_;
		int columns_;
};
