#include<string>
#include<iostream>
#pragma once

class Matrix
{
public:
	Matrix(int rows, int cols);
	class Row
	{
		friend class Matrix;
	public:
		double& operator[](int j) const
		{
			return parent.elem[row][j];
		}
	private:
		Row(Matrix& parent, int row) : parent{ parent }, row{ row } {};
		Matrix& parent;
		int row;
	};
	const Row operator[](int i)
	{
		return Row(*this, i);
	}

	Matrix& operator=(const Matrix& m);
	Matrix operator*(const Matrix& a);
	friend Matrix operator+(const Matrix& a, const Matrix& b);
	Matrix operator-(const Matrix& a);
	friend std::ostream& operator<<(std::ostream& os, const Matrix &a);
	void zeroing();
	~Matrix();
private:
	int rows;
	int cols;
	double** elem;
protected:
};

