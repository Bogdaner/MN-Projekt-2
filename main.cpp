#include<iostream>
#include "Matrix.h"

int main()
{
	Matrix m(5, 5);
	Matrix m2(5, 5);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			m[i][j] = std::rand() % 10;
			m2[i][j] = std::rand() % 10;
		}
	}
	std::cout << m;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << m2;
	std::cout << std::endl; 
	std::cout << std::endl;
	//m = m2;
	Matrix m3 = (m+m2);
	std::cout << m3;
	return 0;
}