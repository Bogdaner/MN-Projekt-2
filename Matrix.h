#include<string>
#include<tuple>
#include<iostream>
#include<fstream>
#pragma once

class Matrix
{
public:
	Matrix(int rows, int cols);
	Matrix(const Matrix& m);
	Matrix(Matrix&& m);

	class Row
	{
		friend class Matrix;
	public:
		double& operator[](int j) const
		{
			return parent.elem[row][j];
		}
	private:
		Row(const Matrix& parent, int row) : parent{ parent }, row{ row } {};
		const Matrix& parent;
		int row;
	};
	const Row operator[](int i) const
	{
		return Row(*this, i);
	}

	Matrix& operator=(const Matrix& m);
	Matrix operator*(const Matrix& a) const;
	Matrix operator+(const Matrix& a) const;
	Matrix operator-(const Matrix& a) const;
	friend std::ostream& operator<<(std::ostream& os, const Matrix &a);
	void zeroing();
	void band_matrix(const int a1,const int a2,const int a3);
	std::tuple<Matrix, Matrix> LU_decomposition() const;
	double get_norm();
	int get_rows() const;
	int get_cols() const;
	void save(const std::string s) const;
	~Matrix();
private:
	int rows;
	int cols;
	double** elem;
protected:
};

