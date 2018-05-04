#include "Matrix.h"

Matrix::Matrix(int rows, int cols) : rows{ rows }, cols{ cols }
{
	std::string Negative_size = "Negative value of number of rows or collumns";
	if (rows < 0 || cols < 0) throw Negative_size;
	elem = new double*[rows];
	for (int i = 0; i < rows; i++)
		elem[i] = new double[cols];
}

Matrix::Matrix(const Matrix& m)
{
	rows = m.rows;
	cols = m.cols;
	elem = new double*[rows];
	for (int i = 0; i < rows; i++)
		elem[i] = new double[cols];

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			elem[i][j] = m.elem[i][j];
}

Matrix::Matrix(Matrix&& m) : elem{ m.elem }, cols{ m.cols }, rows{ m.rows }
{
	m.elem = nullptr;
	m.rows = 0;
	m.cols = 0;
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

Matrix Matrix::operator*(const Matrix& a) const
{
	std::string Wrong_dimensions = "Cant multiply these matrices number of columns of first matrix is different than number of rows of second";
	if (cols != a.rows) throw Wrong_dimensions;
	Matrix result(rows, a.cols);

	result.zeroing();

	for(int i = 0; i < rows; i++)
		for(int j = 0; j < a.cols; j++)
			for (int k = 0; k < cols; k++)
			{
				result.elem[i][j] += elem[i][k] * a.elem[k][j];
			}
	return result;
}

Matrix Matrix::operator-(const Matrix& a) const
{
	std::string Wrong_dimensions = "Cant subtract these matrices different sizes";
	if (cols != a.cols && rows != a.rows) throw Wrong_dimensions;

	Matrix result(rows, cols);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			result.elem[i][j] = elem[i][j] - a.elem[i][j];
		}
	return result;
}

Matrix Matrix::operator+(const Matrix& a) const
{
	std::string Wrong_dimensions = "Cant add these matrices different sizes";
	if (cols != a.cols && rows != a.rows) throw Wrong_dimensions;

	Matrix result(rows, cols);
	for (int i = 0; i < result.rows; i++)
		for (int j = 0; j < result.cols; j++)
		{
			result.elem[i][j] = elem[i][j] + a.elem[i][j];
		}
	return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix& a)
{
	for (int i = 0; i < a.rows; i++)
	{
		for (int j = 0; j < a.cols; j++)
		{
			os << a.elem[i][j] << " ";
		}
		os << std::endl;
	}
	return os;
}

void Matrix::zeroing()
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			elem[i][j] = 0;
}

void Matrix::band_matrix(const int a1, const int a2, const int a3)
{
	std::string Not_square = "Number of rows and cols are different";
	if (rows != cols) throw Not_square;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (i == j)
				elem[i][j] = a1;
			else if (i + 1 == j || i - 1 == j)
				elem[i][j] = a2;
			else if (i + 2 == j || i - 2 == j)
				elem[i][j] = a3;
			else
				elem[i][j] = 0;
		}
	}
}

std::tuple<Matrix, Matrix> Matrix::LU_decomposition() const
{
	std::string Not_square = "Number of rows and cols are different";
	if (rows != cols) throw Not_square;
	Matrix U = *this;
	Matrix L{rows, cols};
	for(int i = 0; i < rows; i++) // L = identity matrix
		for (int j = 0; j < cols; j++)
		{
			if (i == j)
				L[i][j] = 1;
			else
				L[i][j] = 0;
		}

	for(int k = 0; k < rows - 1; k++)
		for (int j = k + 1; j < rows; j++)
		{
			L[j][k] = U[j][k] / U[k][k];
			for (int i = k; i < rows; i++)
				U[j][i] = U[j][i] - (L[j][k] * U[k][i]);
		}

	return std::make_tuple(L, U);
}

double Matrix::get_norm()
{
	double sum = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			sum += std::pow(elem[i][j], 2);

	return std::sqrt(sum);
}

int Matrix::get_rows() const
{
	return rows;
}

int Matrix::get_cols() const
{
	return cols;
}

void Matrix::save(const std::string s) const
{
	std::fstream f{s, f.out};
	if (f.is_open())
	{
		f << *this;
	}
	f.close();
}

Matrix::~Matrix()
{
	if (rows < 0 && cols < 0) return;
	for (int i = 0; i < rows; i++)
		delete[] elem[i];
	delete[] elem;
}