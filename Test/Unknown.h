#pragma once
#include<utility>

namespace math {

	class Unknown {
	public:
		enum class Equation {
			Unknown, OneSolution, TwoSolutions, DoubleSolution, Identity, NoSolutions, TooDifficult
		};

		static const char const* resultTypesStrings[7];

		Unknown();
		Unknown(const Unknown& other);
		const std::pair<double, double>& getValue() const { return this->value; }
		Equation getEquationResultType() const { return m_resultType; }

		Unknown operator+(double a);
		Unknown operator+(Unknown& other);
		Unknown operator-(double a);
		Unknown operator-(Unknown other);
		Unknown operator*(double a);
		Unknown operator*(Unknown other);
		Unknown operator/(double a);

		Unknown& operator == (double a);

		Unknown& operator == (Unknown other) {
			return (*this) - other == 0;
		}

		friend Unknown operator-(double a, Unknown unknown);
		friend Unknown operator+(double a, Unknown unknown);
		friend Unknown operator*(double a, Unknown unknown);
		friend Unknown& operator==(double a, Unknown& unknown);

	private:
		Equation m_resultType;

		std::pair<double, double> value;
		double n, m, b;
		Unknown* m_original;

	};



	static Unknown operator-(double a, Unknown unknown) {
		Unknown temp;
		temp.b = a - unknown.b;
		temp.m = -unknown.m;
		temp.n = -unknown.n;
		temp.m_original = unknown.m_original;
		temp.m_resultType = unknown.m_resultType;
		return temp;
	}

	static Unknown operator+(double a, Unknown unknown) {
		Unknown temp;
		temp.b = a + unknown.b;
		temp.m = unknown.m;
		temp.n = unknown.n;
		temp.m_original = unknown.m_original;
		temp.m_resultType = unknown.m_resultType;
		return temp;
	}

	static Unknown operator*(double a, Unknown unknown) {
		Unknown temp;
		temp.b = a * unknown.b;
		temp.m = a * unknown.m;
		temp.n = a * unknown.n;
		temp.m_original = unknown.m_original;
		temp.m_resultType = unknown.m_resultType;
		return temp;
	}

	static Unknown& operator==(double a, Unknown& unknown)
	{
		return unknown == a;
	}

}