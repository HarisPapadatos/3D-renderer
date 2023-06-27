#pragma once
#include<array>
#include<assert.h>
#include<iostream>
#include<string>

std::string to_string(double num);
/// <summary>
/// Sums up every element of the std::array using the +=
/// T requires to have a += operator overload method if T is a class
/// </summary>
/// <typeparam name="T">
/// The type of the elements that are being added
/// </typeparam>
/// <param name="a">
/// is an std::array of the elements that should be added
/// </param>
/// <param name="bias">
/// is the initialization value of the the return value.
/// Leave blank for default constructor initialization
/// </param>
/// <returns>
/// A T type sum
/// </returns>
template<typename T,size_t N>
T sum(const std::array<T,N>& a,const T& bias =T()) {
	T _toReturn = bias;
	for (auto& i : a) {
		_toReturn += i;
	}
	return _toReturn;
}


namespace math {

	template<size_t R, size_t C>
	class Matrix
	{
	public:
		Matrix();
		Matrix(const std::array<std::array<double, C>, R>&);
		Matrix(const double (&sampleArray)[R][C]);


		constexpr size_t getRowNum() const { return R; }
		constexpr size_t getComulmnNum() const { return C; }
		inline void print()const;
		double getElement(size_t i, size_t j) const;
		void setElement(size_t i, size_t j,double value) const;

		template<size_t R2,size_t C2>
		Matrix<R,C2> operator*(const Matrix<R2,C2>& other)const;

		Matrix<R, C> operator+(const Matrix<R, C>& other)const;
		
		
	private:
		std::array<std::array<double, C>, R> m_elements;
		std::pair<size_t, size_t> largestElement;
		size_t largestElementSize;

		template<size_t R2, size_t C2>
		friend class Matrix;

		static const Matrix<R,R> UnitMatrix;
	};


	template<size_t R, size_t C>
	template<size_t R2, size_t C2>
	Matrix<R, C2> Matrix<R, C>::operator*(const Matrix<R2,C2>& other) const
	{
		//The column number of the first matrix must be equal to the
		//Row number of the second matrix
		assert(C==R2);
		Matrix<R, C2> _toReturn;

		for (unsigned i = 0; i < R; i++) {
			for (unsigned j = 0; j < C2; j++) {
				for (unsigned k = 0; k < C; k++) {
					_toReturn.m_elements[i][j] += this->m_elements[i][k] * other.m_elements[k][j];
				}

				std::string str = to_string(_toReturn.m_elements[i][j]);
				if (str.length() > _toReturn.largestElementSize) {
					_toReturn.largestElementSize = str.length();
					_toReturn.largestElement.first = i;
					_toReturn.largestElement.second = j;
				}

			}
		}


		return _toReturn;
	}

	template<size_t R, size_t C>
	Matrix<R, C> math::Matrix<R, C>::operator+(const Matrix<R, C>& other) const
	{
		Matrix<R, C> _toReturn;

		for (unsigned i = 0; i < R; i++) {
			for (unsigned j = 0; j < C; j++) {
				_toReturn.m_elements[i][j] = this->m_elements[i][j] +other.m_elements[i][j];

				std::string str = to_string(_toReturn.m_elements[i][j]);
				if (str.length() > _toReturn.largestElementSize) {
					_toReturn.largestElementSize = str.length();
					_toReturn.largestElement.first = i;
					_toReturn.largestElement.second = j;
				}

			}
		}

		return _toReturn;
	}



	//Vector type is a Matrix with one column
	template<size_t R>
	using Vector = Matrix<R,1>;

	template<size_t size>
	using SquareMatrix = Matrix<size, size>;

	enum class Axis {
		X,Y,Z,W
	};
}


template<size_t R, size_t C>
math::Matrix<R, C>::Matrix()
{
	largestElement.first = 0;
	largestElement.second = 0;
	largestElementSize = 1;

	//Setting every element to 0
	for (auto& i : m_elements) {
		for (auto& j : i) {
			j = 0;
		}
	}
}

template<size_t R, size_t C>
math::Matrix<R, C>::Matrix(const std::array<std::array<double, C>, R> &sample)
{
	largestElement.first = 0;
	largestElement.second = 0;
	largestElementSize = 1;

	for (size_t i = 0; i < R;i++) {
		for (size_t j = 0; j < C;j++) {
			m_elements[i][j] = sample[i][j];

			//Finding the largest element in digits
			std::string str = to_string(sample[i][j]);
			if (str.length() > largestElementSize) {
				largestElementSize = str.length();
				largestElement.first = i;
				largestElement.second = j;
			}
		}
	}
}

template<size_t R, size_t C>
math::Matrix<R, C>::Matrix(const double (&sampleArray)[R][C])
{
	largestElement.first = 0;
	largestElement.second = 0;
	largestElementSize = 1;

	for (size_t i = 0; i < R; i++) {
		for (size_t j = 0; j < C; j++) {
			m_elements[i][j] = sampleArray[i][j];

			//Finding the largest element in digits
			std::string str = to_string(sampleArray[i][j]);
			if (str.length() > largestElementSize) {
				largestElementSize = str.length();
				largestElement.first = i;
				largestElement.second = j;
			}
		}
	}
}

template<size_t R,size_t C>
inline void math::Matrix<R, C>::print()const {


	for (unsigned j = 0; j < R; j++) {
		for (unsigned i = 0; i < C; i++) {

			//Drawing left boarder
			if (i == 0) 
				if (j == 0) 
					std::cout << "/ ";
				else if (j == R - 1) 
					std::cout << "\\ ";
				else
					std::cout << "| ";
			

			std::cout << m_elements[j][i];

			for (int k = 0; k < largestElementSize - to_string(m_elements[j][i]).length() + 2*(i != C - 1); k++) {

				std::cout << " ";
			}

			if(i==C-1)
				if (j == 0)
					std::cout << " \\";
				else if (j == R - 1)
					std::cout << " /";
				else
					std::cout << " |";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

template<size_t R, size_t C>
double math::Matrix<R, C>::getElement(size_t i, size_t j) const
{
	assert(i <= R && j <= C);
	return m_elements[i+1][j+1];
}

template<size_t R, size_t C>
void math::Matrix<R, C>::setElement(size_t i, size_t j,double value) const
{
	assert(i <= R && j <= C);
	m_elements[i + 1][j + 1]= value;
}
