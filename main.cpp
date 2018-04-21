#include<iostream>
#include "Matrix.h"

int main()
{
	Matrix m(5, 5);

	//for (int i = 0; i < 5; i++)
	//{
	//	for (int j = 0; j < 5; j++)
	//	{
	//		m[i][j] = 5;;
	//	}
	//}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			std::cout << m[i][j];
		}
	}
	return 0;
}