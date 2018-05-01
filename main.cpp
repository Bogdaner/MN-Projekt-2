#include<iostream>
#include "Matrix.h"

int main()
{
	const int c = 9;
	const int d = 3;
	const int e = 4;
	const int N = 9 * c*d;

	Matrix m{ 20, 20 };
	m.band_matrix(1, 2, 3);
	std::cout << m;
	return 0;
}