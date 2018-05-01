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
	return -1;
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
	return -1;
}

Matrix LU_solve(const Matrix& A, const Matrix& b)
{
	const int N = A.get_rows();
	Matrix L{ N, N }, U{ N, N };
	std::tie(L, U) = A.LU_decomposition();

	Matrix y{ N, 1 };
	//creating y temporary vector and solving Ly = b by using forward substitution
	y[0][0] = b[0][0] / L[0][0]; 
	for (int i = 1; i < N; i++)
	{
		double sum = 0;
		for (int j = 0; j < i; j++)
			sum += L[i][j] * y[j][0];

		y[i][0] = (1 / L[i][i])*(b[i][0] - sum);
	}
	//getting result Ux = y back substitution
	Matrix x{ N, 1 };
	x[N - 1][0] = y[N - 1][0] / U[N - 1][N - 1];
	for (int i = N - 2; i >= 0; i--)
	{
		double sum = 0;
		for (int j = i + 1; j <= N - 1; j++)
			sum += U[i][j] * x[j][0];
		
		x[i][0] = (1 / U[i][i])*(y[i][0] - sum);
	}
	return x;
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
		b[i][0] = sin(i*(f + 1));

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
	A2.band_matrix(3, -1, -1);

	Matrix x3{ N , 1 };
	for (int i = 0; i < N; i++)
		x3[i][0] = 1;

	Matrix x4{ N , 1 };
	for (int i = 0; i < N; i++)
		x4[i][0] = 1;

	//int h3 = jacobi(A2, b, x3);
	//int h4 = gauss_siedel(A2, b, x4);
	
	Matrix s = LU_solve(A2, b);

	x.save("jacobi.txt");
	x2.save("siedel.txt");
	s.save("LU.txt");


	return 0;
}