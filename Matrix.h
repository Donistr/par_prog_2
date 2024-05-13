#pragma once

class Matrix {
private:
	int** data;
	size_t rows;
	size_t columns;
public:
	Matrix(size_t rows, size_t columns);

	~Matrix();

	void fillMatrixRandomNumbers(int maxNumber);

	void printMatrix() const;

	Matrix& multiply(const Matrix& matrix) const;

	const int& get(size_t row, size_t column) const;

	size_t getRows() const;

	size_t getColumns() const;
};