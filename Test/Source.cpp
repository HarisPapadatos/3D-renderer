#include<iostream>
#include<Windows.h>
#include"Matrix.h"
#include"Unknown.h"


int main() {
	math::Matrix<3, 3> matrix1;
	math::Matrix<3, 3> matrix2;
	
	double sample1[3][3] = {
		{
			{1},{0},{7}
		},
		{	
			{2},{1},{0}
		},
		{
			{0},{4},{1}
		}
	};

	double sample2[3][3] = {
		{
			{1},{3},{4}
		},
		{
			{2},{4},{1}
		},
		{
			{6},{1},{9}
		}
	};
	matrix1 = sample1;
	matrix2 = sample2;

	matrix1.print();
	std::endl(std::cout);
	matrix2.print();
	std::endl(std::cout);

	math::Matrix<3, 3> matrixProduct = (matrix1 + matrix2);
	matrixProduct.print();


	std::cin.get();
}
