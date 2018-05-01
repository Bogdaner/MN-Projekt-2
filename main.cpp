#include<iostream>
#include "Matrix.h"


int jacobi(const Matrix& A, const Matrix& b, Matrix& x)
{
	for (int iter = 0; iter < 1000; iter++)
	{
		Matrix prev_x = x;
		for (int i = 0; i < x.get_rows(); i++)
		{
			double sum1 = 0;
			for (int j = 0; j < i; j++)
				sum1 += A[i][j] * prev_x[j][0];

			double sum2 = 0;
			for (int j = i + 1; j < A.get_rows(); j++)
				sum2 += A[i][j] * prev_x[j][0];

			x[i][0] = (b[i][0] - sum1 - sum2) / A[i][i];
		}
		Matrix res = (A*x) - b;
		if (res.get_norm() < 1e-9)
			return iter + 1;
	}
}

int gauss_siedel(const Matrix& A, const Matrix& b, Matrix& x)
{
	for (int iter = 0; iter < 1000; iter++)
	{
		for (int i = 0; i < x.get_rows(); i++)
		{
			double sum1 = 0;
			for (int j = 0; j < i; j++)
				sum1 += A[i][j] * x[j][0];

			double sum2 = 0;
			for (int j = i + 1; j < A.get_rows(); j++)
				sum2 += A[i][j] * x[j][0];

			x[i][0] = (b[i][0] - sum1 - sum2) / A[i][i];
		}
		Matrix res = (A*x) - b;
		if (res.get_norm() < 1e-9)
			return iter + 1;
	}
}

int main()
{
	const int c = 9;
	const int d = 3;
	const int e = 4;
	const int f = 5;
	const int N = 9 * c*d;

	//A matrix init
	Matrix A{ N, N };
	A.band_matrix(5 + e, -1, -1);

	//b vector init
	Matrix b{ N, 1 };
	for (int i = 0; i < N; i++)
		b[i][0] = sin((i + 1)*(f + 1));

	//init x vector
	Matrix x{ N , 1 };
	for (int i = 0; i < N; i++)
		x[i][0] = 1;

	Matrix x2{ N , 1 };
	for (int i = 0; i < N; i++)
		x2[i][0] = 1;
	
	int h = jacobi(A, b, x);
	int h2 = gauss_siedel(A, b, x2);
	////////////////////////////////////////////////////////

	Matrix A2{ N,N };
	A.band_matrix(3, -1, -1);

	Matrix x3{ N , 1 };
	for (int i = 0; i < N; i++)
		x3[i][0] = 1;

	Matrix x4{ N , 1 };
	for (int i = 0; i < N; i++)
		x4[i][0] = 1;

	//int h3 = jacobi(A, b, x);
	//int h4 = gauss_siedel(A, b, x2);


	return 0;
}