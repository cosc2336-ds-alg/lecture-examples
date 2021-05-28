/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   February 2, 2019
 * @assg   ComplexNumber
 *
 * @description ComplexNumber class, used for examples of overloading.
 */
#include <iostream>
using namespace std;

#ifndef COMPLEXNUMBER_HPP
#define COMPLEXNUMBER_HPP

/** Complex Numbers
 * Add a complex number data type to the C++ language.
 * A complex number is a number that can be expressed in the
 * form a + bi where a and b are rel numbers and i = sqrt(-1)
 * (an imaginary number).  a is the real part, and b is the
 * imaginary part.
 *
 * @var realPart The real part of this complex number (a double)
 * @var imaginaryPart The imaginary part of this complex number (a double)
 */
class ComplexNumber
{
private:
  double realPart;      // real part of the complex number
  double imaginaryPart; // imaginary part of the complex number

public:
  ComplexNumber();                              // default constructor
  ComplexNumber(double real, double imaginary); // common constructor

  // overloaded operators, addition, subtraciton, multiplication,
  // reciprocal, division
  ComplexNumber operator+(const ComplexNumber rhs);
  ComplexNumber& operator+=(const ComplexNumber rhs);
  ComplexNumber operator-(const ComplexNumber rhs);
  ComplexNumber& operator-=(const ComplexNumber rhs);
  ComplexNumber operator*(const ComplexNumber rhs);
  ComplexNumber& operator*=(const ComplexNumber rhs);

  ComplexNumber reciprocal() const;
  ComplexNumber operator~() const; // overload as reciprocal
  ComplexNumber operator/(const ComplexNumber rhs);

  // boolean comparison operators
  bool operator<(const ComplexNumber rhs);

  // scalar operations, add, subtract and multiply by a scalar
  // value (a scalr is a simple single double)
  ComplexNumber operator+(double rhs);
  ComplexNumber operator-(double rhs);
  ComplexNumber operator*(double rhs);

  // overload assignment
  const ComplexNumber& operator=(const ComplexNumber& rhs);

  // overload indexing
  double& operator[](const int index);

  // overload output stream function (needs to be a friend function
  string tostring() const;
  friend ostream& operator<<(ostream& out, const ComplexNumber& aComplexNumber);
};

#endif
