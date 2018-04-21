#include<string>
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

	~Matrix();
private:
	int rows;
	int cols;
	double** elem;
protected:
};

