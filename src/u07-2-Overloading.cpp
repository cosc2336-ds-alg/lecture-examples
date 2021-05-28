/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   February 2, 2019
 * @assg   Overloading
 *
 * @description Examples of Function Overloading and Operator
 *   Overloading.
 */
#include <cmath>
#include <iostream>
#include <sstream>
using namespace std;

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
  ComplexNumber(double real, double imaginary); // common constructor

  // overloaded operators, addition, subtraciton, multiplication,
  // reciprocal, division
  ComplexNumber operator+(const ComplexNumber rhs);
  ComplexNumber operator-(const ComplexNumber rhs);
  ComplexNumber operator*(const ComplexNumber rhs);

  ComplexNumber reciprocal() const;
  ComplexNumber operator~() const; // overload as reciprocal
  ComplexNumber operator/(const ComplexNumber rhs);

  // overload assignment
  const ComplexNumber& operator=(const ComplexNumber& rhs);

  // overload InheritanceCompositionindexing
  double& operator[](const int index);

  // overload output stream function (needs to be a friend function
  string tostring() const;
  friend ostream& operator<<(ostream& out, const ComplexNumber& aComplexNumber);
};

/** ComplexNumber default constructor
 * Constructor for ComplexNumber.  Technically this is not the default
 * constructor, but since both of the parameters default to 0.0 if not
 * specified, this constructor will also construct classes if no
 * initial values for the real and imaginary parts are given.
 *
 * @param real The initial value for the realPart of this complex number,
 *   defaults to 0.0 if not specified.
 * @param imaginary The initial value of the imaginary part of this complex
 *   number, dInheritanceCompositionefaults to 0.0 if not specified.
 */
ComplexNumber::ComplexNumber(double real = 0.0, double imaginary = 0.0)
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

/** ComplexNumInheritanceCompositionber reciprocal
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
  cout << "<ComplexNumber::operator=> LOG: assignment entered"
       << " this=" << *this << " rhs=" << rhs << endl;

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

  // return 0.0 by default if invalid index given
  // this is actually illegal, and dangerous, we are returning a reference to a local variable
  double value = 0.0;
  return value;
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

/** minimum of doubles
 * A quick example of function overloading, first we define minimum
 * for two doubles
 *
 * @param left, right - Two double values to compare.
 *
 * @returns double Returns the minimum of the two given values
 */
double minimum(double left, double right)
{
  if (left < right)
  {
    return left;
  }
  else
  {
    return right;
  }
}

/** Minimum of ComplexNumbers
 * Example of overloading function.  Find minimum of two
 * ComplexNumber types.  Notice name is overloaded.  As long
 * as the "function signature" is different, we can overload
 * a function name.
 *
 * @param left, right - Two ComplexNumber types, we want to compare
 *   them and return the smaller of the two.
 *
 * @returns ComplexNumber Returns the minimum of the two given
 *   ComplexNumbers.
 */
ComplexNumber minimum(ComplexNumber left, ComplexNumber right)
{
  // if real part differs, it determins the ordering
  // Use the array indexing as getter methods here.
  if (left[1] < right[1])
  {
    return left;
  }
  else if (left[1] > right[1])
  {
    return right;
  }
  // if real part equal, default to imaginary part
  else if (left[2] < right[2])
  {
    return left;
  }
  else
  {
    return right;
  }
}

/** main
 * The main entry point for this program.  Execution of this program
 * will begin with this main function.
 *
 * @param argc The command line argument count which is the number of
 *     command line arguments provided by user when they started
 *     the program.
 * @param argv The command line arguments, an array of character
 *     arrays.
 *
 * @returns An int value indicating program exit status.  Usually 0
 *     is returned to indicate normal exit and a non-zero value
 *     is returned to indicate an error condition.
 */
int main(int argc, char** argv)
{
  // example of the default constructor
  ComplexNumber c1;
  cout << "c1: " << c1 << endl;

  // example of additional constructor
  ComplexNumber c2(3.5, 2.8);
  cout << "c2: " << c2 << endl;

  // complex numbers where imaginary part is negative
  ComplexNumber c3(1.8, -4.5);
  cout << "c3: " << c3 << endl;

  // operator+ and operator- binary operators for ComplexNumbers
  cout << "c2 + c3 = " << (c2 + c3) << endl;
  cout << "c2 - c3 = " << (c2 - c3) << endl;

  // question, why doesn't this invoke assignment operator?
  cout << "Performing assignment:" << endl;
  ComplexNumber c4 = c2 - c3;
  cout << "c4: " << c4 << endl;

  // example of assignment operator, it does work if explicitly
  // used in a non declaration statement.
  ComplexNumber c5;
  c5 = c2 - c3;
  cout << "c5: " << c5 << endl;

  // some more binary operators, operator*
  cout << "c2 * c3 = " << (c2 * c3) << endl;

  // an example of a unary operator
  // we could define increment and decrement, here we show overloading ~
  // to mean reciprocal
  cout << "1/c2 = " << c2.reciprocal() << endl;
  cout << "1/c2 = " << ~c2 << endl;

  // make binary operator/ definition simple in terms of reciprocal
  cout << "c3 / c2 = " << (c3 / c2) << endl;

  // example of array subscripting
  cout << "c5 real part: " << c5[1] << endl;
  cout << "c5 imaginary part: " << c5[2] << endl;

  // since we return a reference, we can actually use this for our setter
  // as well
  c5[1] = 42.42;
  c5[2] = -1.234;
  cout << "after changing c5 real and imaginary parts, we have: " << c5 << endl;

  // example of operator overloading
  cout << "minimum of 3.5 and 8.7: " << minimum(3.5, 8.7) << endl;
  cout << "minimum of c5 and c3: " << minimum(c5, c3) << endl;

  // return 0 to indicate successful completion from main function
  // and our program
  return 0;
}