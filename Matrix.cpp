#include "Matrix.h"

Matrix::Matrix(int rows, int cols) : rows{ rows }, cols{ cols }
{
	std::string Negative_size = "Negative value of number of rows or collumns";
	if (rows < 0 || cols < 0) throw Negative_size;
	elem = new double*[rows];
	for (int i = 0; i < rows; i++)
		elem[i] = new double[cols];
}

Matrix& Matrix::operator=(const Matrix& m)
{
	double** p = new double*[m.rows];
	for (int i = 0; i < m.rows; i++)
		p[i] = new double[m.cols];

	for (int i = 0; i < m.rows; i++)
		for (int j = 0; j < m.cols; j++)
			p[i][j] = m.elem[i][j];

	this->~Matrix();

	elem = p;
	rows = m.rows;
	cols = m.cols;
	return *this;
}

Matrix Matrix::operator*(const Matrix a) const
{
	std::string Wrong_dimensions = "Cant multiply these matrices number of columns of first matrix is different than number of rows of second";
	if (cols != a.rows) throw Wrong_dimensions;
	Matrix result(rows, a.cols);

	for (int i = 0; i < result.rows; i++)
		for (int j = 0; j < result.cols; j++)
			result.elem[i][j] = 0;

	for(int i = 0; i < rows; i++)
		for(int j = 0; j < a.cols; j++)
			for (int k = 0; k < cols; k++)
			{
				result.elem[i][j] += elem[i][k] * a.elem[k][j];
			}
	return result;
}

Matrix Matrix::operator+(const Matrix a) const
{
	std::string Wrong_dimensions = "Cant multiply these matrices number of columns of first matrix is different than number of rows of second";
	if (cols != a.cols && rows != a.rows) throw Wrong_dimensions;
	Matrix result(rows, cols);

	for (int i = 0; i < result.rows; i++)
		for (int j = 0; j < result.cols; j++)
			result.elem[i][j] = 0;

	for(int i =0 ; i<rows;i++)
		for (int j = 0; j < cols; j++)
		{
			result.elem[i][j] += elem[i][j] + a.elem[i][j];
		}
	return result;
}

Matrix::~Matrix()
{
	if (rows > 0 && cols > 0) return;
	for (int i = 0; i < rows; i++)
		delete[] elem[i];
	delete[] elem;
}
