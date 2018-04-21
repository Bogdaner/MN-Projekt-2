#include "Matrix.h"

Matrix::Matrix(int rows, int cols) : rows{ rows }, cols{ cols }
{
	std::string Negative_size = "Negative value of number of rows or collumns";
	if (rows < 0 || cols < 0) throw Negative_size;
	elem = new double*[rows];
	for (int i = 0; i < rows; i++)
		elem[i] = new double[cols];
}

Matrix::~Matrix()
{
	for (int i = 0; i < rows; i++)
		delete[] elem[i];

	delete[] elem;
}
