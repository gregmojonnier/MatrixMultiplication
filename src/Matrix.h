#include <utility>
#include <vector>

class Matrix {
	public:
		Matrix(int rows, int columns, int start_value=0);

		int rows() const noexcept;
		int columns() const noexcept;

		int get_value(std::pair<int, int> cell) const;
		void set_value(std::pair<int, int> cell, int value);

		int sum() const noexcept;
	private:
		void verify_cell_validity(int row, int column) const;

		std::vector<std::vector<int>> matrix_;
		int rows_;
		int columns_;
};
