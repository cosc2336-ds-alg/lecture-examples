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
#include "ComplexNumber.hpp"
#include <cmath>
#include <iostream>
#include <sstream>
using namespace std;

/** ComplexNumber default constructor
 * Constructor for ComplexNumber.  This is a true default constructor.
 */
ComplexNumber::ComplexNumber()
{
  realPart = 0.0;
  imaginaryPart = 0.0;
}

/** ComplexNumber common constructor
 * Constructor for ComplexNumber.  Common constructor case, give the real
 * and imaginary parts of the ComplexNumber to create.
 *
 * @param real The initial value for the realPart of this complex number,
 *   defaults to 0.0 if not specified.
 * @param imaginary The initial value of the imaginary part of this complex
 *   number, defaults to 0.0 if not specified.
 */
ComplexNumber::ComplexNumber(double real, double imaginary)
{
  realPart = real;
  imaginaryPart = imaginary;
}

/** ComplexNumber addition
 * Override the binary addition + to provide addition between
 * two complex numbers.
 *
 * @param rhs The other ComplexNumber on the right hand side
 *   of the addition being performed.
 *
 * @returns ComplexNumber A new ComplexNumber is created and
 *   returned which is the result of adding this + rhs
 */
ComplexNumber ComplexNumber::operator+(const ComplexNumber rhs)
{
  double realResult = realPart + rhs.realPart;
  double imaginaryResult = imaginaryPart + rhs.imaginaryPart;
  ComplexNumber result(realResult, imaginaryResult);
  return result;
}

/** ComplexNumber addition and assignments
 * Override the binary addition + to provide addition between
 * two complex numbers.
 *
 * @param rhs The other ComplexNumber on the right hand side
 *   of the addition being performed.
 *
 * @returns ComplexNumber The assignment is going back to ourself,
 *   so we simply update our real and imaginary parts and return
 *   a reference to this
 */
ComplexNumber& ComplexNumber::operator+=(const ComplexNumber rhs)
{
  realPart += rhs.realPart;
  imaginaryPart += rhs.imaginaryPart;

  return *this;
}

/** ComplexNumber subtraction
 * Override the binary addition - to provide subtraction between
 * two complex numbers.
 *
 * @param rhs The other ComplexNumber on the right hand side
 *   of the subtraction being performed.
 *
 * @returns ComplexNumber A new ComplexNumber is created and
 *   returned which is the result of adding this - rhs
 */
ComplexNumber ComplexNumber::operator-(const ComplexNumber rhs)
{
  double realResult = realPart - rhs.realPart;
  double imaginaryResult = imaginaryPart - rhs.imaginaryPart;
  ComplexNumber result(realResult, imaginaryResult);
  return result;
}

/** ComplexNumber subtraction and assignments
 * Override the binary addition -= to provide addition between
 * two complex numbers.
 *
 * @param rhs The other ComplexNumber on the right hand side
 *   of the addition being performed.
 *
 * @returns ComplexNumber The assignment is going back to ourself,
 *   so we simply update our real and imaginary parts and return
 *   a reference to this
 */
ComplexNumber& ComplexNumber::operator-=(const ComplexNumber rhs)
{
  realPart -= rhs.realPart;
  imaginaryPart -= rhs.imaginaryPart;

  return *this;
}

/** ComplexNumber multiplication
 * Override the binary addition * to provide multiplication between
 * two complex numbers.
 *
 * (x + yi) * (u + vi) = (xu - yv) + (xv + yu)i
 *
 * @param rhs The other ComplexNumber on the right hand side
 *   of the multiplication being performed.
 *
 * @returns ComplexNumber A new ComplexNumber is created and
 *   returned which is the result of multiplying this * rhs
 */
ComplexNumber ComplexNumber::operator*(const ComplexNumber rhs)
{
  double realResult;
  realResult = (realPart * rhs.realPart - imaginaryPart * rhs.imaginaryPart);
  double imaginaryResult;
  imaginaryResult = (realPart * rhs.imaginaryPart + imaginaryPart * rhs.realPart);
  ComplexNumber result(realResult, imaginaryResult);
  return result;
}

/** ComplexNumber multiplication and assignments
 * Override the binary addition *= to provide addition between
 * two complex numbers.
 *
 * @param rhs The other ComplexNumber on the right hand side
 *   of the addition being performed.
 *
 * @returns ComplexNumber The assignment is going back to ourself,
 *   so we simply update our real and imaginary parts and return
 *   a reference to this
 */
ComplexNumber& ComplexNumber::operator*=(const ComplexNumber rhs)
{
  // need to be careful not to use the updated real part
  // in the next calculations, so put in temporary first
  double realResult;
  realResult = (realPart * rhs.realPart - imaginaryPart * rhs.imaginaryPart);
  double imaginaryResult;
  imaginaryResult = (realPart * rhs.imaginaryPart + imaginaryPart * rhs.realPart);

  // update this for the multiplication result
  this->realPart = realResult;
  this->imaginaryPart = imaginaryResult;

  // return ourself as the result of assignment
  return *this;
}

/** ComplexNumber reciprocal
 * Compute the reciprocal of this complex number.  We
 * create a new complex number to return.  The
 * reciprocal of a complex number z = x + yi is 1/z and is
 * equal to
 *
 * 1/z = x/(x^2 + y^2) - y/(x^2 + y^2) i
 *
 * @returns This function returns a new ComplexNumber
 *   which is the result of calculating the reciprocal
 *   of this complex number.
 */
ComplexNumber ComplexNumber::reciprocal() const
{
  // both resulting real and imaginary parts are divided
  // by the same divisor in calculating the reciprocal
  double divisor;
  divisor = pow(realPart, 2.0) + pow(imaginaryPart, 2.0);

  double realResult = realPart / divisor;
  double imaginaryResult = -imaginaryPart / divisor;
  ComplexNumber result(realResult, imaginaryResult);
  return result;
}

/** ComplexNumber overload ~ for reciprocal
 * We reuse the ~ operator (bitwise NOT) and redefine
 * it as a uniary operator that means reciprocal
 * for ComplexNumbers.  The actual work of
 * calculating the reciprocal of this ComplexNumber
 * is left to the reciprocal() member function.
 *
 * @returns This function returns a new ComplexNumber
 *   which is the result of calculating the reciprocal
 *   of this complex number.
 */
ComplexNumber ComplexNumber::operator~() const
{
  return reciprocal();
}

/** ComplexNumber division
 * Override the binary / to provide division between
 * two complex numbers. We use the definition of
 * the reciprocal of a complex number to accomplish
 * division. if w and z are complex numbers then
 *
 *   w / z = w * (1/z)
 * And thus if we can calculate the reciprocal of the
 * rhs, we can reuse multiplication.
 *
 * @param rhs The other ComplexNumber on the right hand side
 *   of the division being performed.
 *
 * @returns ComplexNumber A new ComplexNumber is created and
 *   returned which is the result of dividing this * rhs
 */
ComplexNumber ComplexNumber::operator/(const ComplexNumber rhs)
{
  // notice we have to dereference *this so that we can correctly
  // invoke the operator* between two ComplexNumbers
  return (*this) * rhs.reciprocal();
}

/** ComplexNumber less than operator
 * Overload less than operator to provide basic
 * comparisons between complex numbers.
 *
 * @param rhs The other number on right hand side of the boolean
 *   less than comparison we are comparing this to.
 *
 * @returns bool True if this complex number is less than the
 *   other rhs number, false other wise.
 */
bool ComplexNumber::operator<(const ComplexNumber rhs)
{
  if (realPart < rhs.realPart)
  {
    return true;
  }
  else if (realPart > rhs.realPart)
  {
    return false;
  }
  else if (imaginaryPart < rhs.imaginaryPart)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/** ComplexNumber scalar addition
 * Add a scalar value (a double or a int for example will be
 * automatically cast by C++).  A scalar number x, is simply
 * x + 0i in complex form, e.g. the imaginary part is 0.
 *
 * @param rhs The right hand side, a simple numeric value of type
 *   double (or may be an int that will be typecase by C++ to a
 *   double).
 *
 * @returns ComplexNumber A new ComplexNumber is created and the
 *   result of adding the scalar to this is calculated and returned
 *   as this new value.
 */
ComplexNumber ComplexNumber::operator+(double rhs)
{
  double realResult = realPart + rhs;
  ComplexNumber result(realResult, imaginaryPart);
  return result;
}

/** ComplexNumber scalar subtraction
 * Subtract a scalar value (a double or a int for example will be
 * automatically cast by C++).  A scalar number x, is simply
 * x + 0i in complex form, e.g. the imaginary part is 0.
 *
 * @param rhs The right hand side, a simple numeric value of type
 *   double (or may be an int that will be typecase by C++ to a
 *   double).
 *
 * @returns ComplexNumber A new ComplexNumber is created and the
 *   result of subtracting the scalar to this is calculated and returned
 *   as this new value.
 */
ComplexNumber ComplexNumber::operator-(double rhs)
{
  double realResult = realPart - rhs;
  ComplexNumber result(realResult, imaginaryPart);
  return result;
}

/** ComplexNumber scalar multiplication
 * Multiply a scalar value (a double or a int for example will be
 * automatically cast by C++).  A scalar number x, is simply
 * x + 0i in complex form, e.g. the imaginary part is 0.
 *
 * @param rhs The right hand side, a simple numeric value of type
 *   double (or may be an int that will be typecase by C++ to a
 *   double).
 *
 * @returns ComplexNumber A new ComplexNumber is created and the
 *   result of multiplying the scalar to this is calculated and returned
 *   as this new value.
 */
ComplexNumber ComplexNumber::operator*(double rhs)
{
  double realResult = realPart * rhs;
  double imaginaryResult = imaginaryPart * rhs;
  ComplexNumber result(realResult, imaginaryResult);
  return result;
}

/** ComplexNumber overload assignment
 * Example of overloading the assignment operator.  For our
 * ComplexNumber this is actually unnecessary as this is the
 * default behavior of the assignment (copy all member variables).
 * But overloading assignment can be necessary, for example if you
 * need to make a deep copy of an array.
 *
 * @param rhs The right hand side of the x = rhs assignment we are
 *   handling.  Rhs should be copied into this ComplexNumber
 *
 * @returns Return a reference to ourself *this as a result of
 *   the assignment, because all assignments evaluate to the
 *   resulting assigned variable.
 */
const ComplexNumber& ComplexNumber::operator=(const ComplexNumber& rhs)
{
  // avoid self-assignment, if objects are different, copy
  // member variables (if they are some, we don't do anything)
  // cout << "<ComplexNumber::operator=> LOG: assignment entered"
  //     << " this=" << *this
  //     << " rhs=" << rhs << endl;

  if (this != &rhs)
  {
    this->realPart = rhs.realPart;
    this->imaginaryPart = rhs.imaginaryPart;
  }

  // assignment expressions always result in the variable/value that
  // was assigned, so return a reference to this ComplexNumber
  return *this;
}

/** ComplexNumber subscript operator
 * Again may not be a realistic thing to do, but as an example of
 * overriding the subscript operator [], we define subscript [1]
 * as the realPart and subscript [2] as the imaginaryPart.  All other
 * subscripts will return 0.0/
 *
 * @param index An integer index value, only indexs 1 and 2 return
 *   anything meaningful from a ComplexNumber, returning the
 *   realPart and the imaginaryPart respectively.
 *
 * @returns double& Returns a reference to the real or imaginary
 *   part, or to 0.0 if index 1 or 2 not used.
 */
double& ComplexNumber::operator[](const int index)
{
  if (index == 1)
  {
    return realPart;
  }
  else if (index == 2)
  {
    return imaginaryPart;
  }

  cerr << "<ComplexNumber::operator[]> ERROR: invalid index: " << index << endl
       << "   Valid indexes are 1 for real part, 2 for imaginary part" << endl;
  exit(0);
}

/** ComplexNumber convert to string
 * Convert a ComplexNumber to a string representation
 *
 * @returns string Returns a string representation of
 *   this ComplexNumber
 */
string ComplexNumber::tostring() const
{
  ostringstream out;

  out << "( " << realPart;

  // make look prettier, if imaginary part is negative
  if (imaginaryPart >= 0)
  {
    out << " + " << imaginaryPart;
  }
  else
  {
    out << " - " << -imaginaryPart;
  }
  out << " i )";

  return out.str();
}

/** overload stream output operator <<
 * Friend function of ComplexNumber to overload the output
 * stream operator<<, provides output representation to
 * a standard ostream of the passed in ComplexNumber.
 *
 * @param out An output stream to which we are to send a representation
 *   of a ComplexNumber.
 * @param aComplexNumber The ComplexNumber we are to represent out to
 *   the output stream.
 *
 * @returns ostream Returns the output stream but after we have inserted
 *   the complex number into the stream.
 */
ostream& operator<<(ostream& out, const ComplexNumber& aComplexNumber)
{
  out << aComplexNumber.tostring();
  return out;
}
