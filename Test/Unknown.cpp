#include "Unknown.h"
using math::Unknown;

Unknown::Unknown() {
	value = { 0,0 };
	m = 1;
	b = 0;
	n = 0;
	m_original = this;
	m_resultType = Equation::Unknown;
}

Unknown::Unknown(const Unknown& other) {
	value = other.value;
	m = other.m;
	b = other.b;
	n = other.n;
	m_resultType = other.m_resultType;
	m_original = other.m_original;
}

Unknown& Unknown::operator == (double a) {

	if (m_original->m_resultType == Equation::TooDifficult)
		return *this;

	if (n == 0) {
		if (m != 0) {
			m_original->value.first = (a - b) / m;
			m_original->value.second = (a - b) / m;
			m_original->m_resultType = Equation::OneSolution;
		}
		else if (a - b == 0) {
			m_original->m_resultType = Equation::Identity;
		}
		else
			m_original->m_resultType = Equation::NoSolutions;

	}
	else {
		double D = m * m - 4 * (b - a) * n;
		if (D < 0) {
			m_original->m_resultType = Equation::NoSolutions;
		}
		else if (D > 0) {
			m_original->value.first = (-m + sqrt(D)) / (2 * n);
			m_original->value.second = (-m - sqrt(D)) / (2 * n);
			m_original->m_resultType = Equation::TwoSolutions;
		}
		else
		{
			m_original->value.first = -m / (2 * n);
			m_original->value.second = -m / (2 * n);
			m_original->m_resultType = Equation::DoubleSolution;
		}
	}
	return (*m_original);
}

Unknown Unknown::operator+(double a) {
	Unknown temp(*this);
	temp.b += a;
	return temp;
}

Unknown Unknown::operator+(Unknown& other) {
	Unknown temp(*this);
	temp.n += other.m;
	temp.m += other.m;
	temp.b += other.b;
	return temp;

}

Unknown Unknown::operator-(double a) {
	Unknown temp(*this);
	temp.b -= a;
	return temp;
}

Unknown Unknown::operator-(Unknown other) {
	Unknown temp(*this);
	temp.n -= other.n;
	temp.m -= other.m;
	temp.b -= other.b;
	return temp;
}

Unknown Unknown::operator*(double a) {
	Unknown temp(*this);
	temp.n *= a;
	temp.m *= a;
	temp.b *= a;
	return temp;
}

Unknown Unknown::operator*(Unknown other) {
	if (n * other.n == 0 && (m * other.n + n * other.m) == 0) {
		Unknown temp(*this);

		temp.n = (other.n * b + other.m * m + other.b * n);
		temp.m = (other.m * b + m * other.b);
		temp.b = other.b * b;
		return temp;
	}
	else {
		m_original->m_resultType = Equation::TooDifficult;
		return *this;
	}
}

Unknown Unknown::operator/(double a) {
	Unknown temp(*this);
	temp.n /= a;
	temp.m /= a;
	temp.b /= a;
	return temp;
}