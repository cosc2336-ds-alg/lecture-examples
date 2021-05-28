/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   February 2, 2019
 * @assg   Templates
 *
 * @description Examples of Function Templates and Class templates
 */
#include "ComplexNumber.hpp"
#include "Vector.hpp"
#include <iostream>
using namespace std;

/** minimum template
 * Write a minimum function once and for all.  Should work for built
 * in types (like int, double), and for any defined type that supports
 * the operator<
 *
 * @param left, right Parameters of template Type, both of the same type,
 *   to be compared to see which is smaller.
 *
 * @returns Type Returns either the given left or right Type input, depending
 *   on which is the smaller according to operator<
 */
template<class T>
T minimum(T left, T right)
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
  // Example of function template, does it work on built in types?
  int leftInt = 5, rightInt = 10;
  int minInt;
  minInt = minimum(leftInt, rightInt);
  cout << "The minimum of integers: " << leftInt << " and " << rightInt << " : " << minInt << endl;
  cout << "The minimum of integers: " << rightInt << " and " << leftInt << " : " << minimum(rightInt, leftInt) << endl;
  cout << endl;

  double leftDouble = 5.55, rightDouble = 10.1010;
  double minDouble;
  minDouble = minimum(leftDouble, rightDouble);
  cout << "The minimum of doubles: " << leftDouble << " and " << rightDouble << " : " << minDouble << endl;
  cout << "The minimum of doubles: " << 42.5 << " and " << -33.3 << " : " << minimum(42.5, -33.3) << endl;
  cout << endl;

  string leftString = "Derek";
  string rightString = "Billy";
  string minString = minimum(leftString, rightString);
  cout << "The minimum of strings: " << leftString << " and " << rightString << " : " << minString << endl;

  ComplexNumber leftNumber(1.5, 3.8);
  ComplexNumber rightNumber(3.8, 2.7);
  cout << "The minimum of ComplexNumbers: " << leftNumber << " and " << rightNumber << " : " << minimum(leftNumber, rightNumber) << endl;
  cout << endl << endl;

  // Example of Class Template, we "templatize" our SeriesCalculation class
  // from Week 03 on Dynamic Memory
  // vector of ints
  const int VECTOR_SIZE = 5;
  int vectorValues[VECTOR_SIZE] = {1, 2, 3, 4, 5};
  Vector<int> v(VECTOR_SIZE, vectorValues);

  cout << v << endl;

  // test series summation, product and difference functions
  // cout << "Summation of series v: " << v.summation() << endl;
  // cout << "Product of series v: " << v.product() << endl;
  // cout << "Difference of series v: " << v.difference() << endl << endl;

  //// test series scalar operations
  cout << "Scalar addition v + 7: " << v + 7 << endl;
  cout << "Scalar operations should return a new vector, so v should still be same:" << endl;
  cout << v << endl;

  // cout << "Scalar multiplication v * -3: " << v * -3 << endl;
  cout << "Vectorized boolean comparison v < 4: " << (v < 4) << endl << endl;

  // lets test with Vector<ComplexNumber>
  ComplexNumber vcnValues[VECTOR_SIZE] = {
    ComplexNumber(1.0, 1.0), ComplexNumber(-1.0, -1.0), ComplexNumber(3.0, -3.0), ComplexNumber(-2.0, 2.0), ComplexNumber(1.28, -3.456)};

  Vector<ComplexNumber> vcn(VECTOR_SIZE, vcnValues);

  cout << vcn << endl;
  // cout << "Summation: " << vcn.summation() << endl;
  cout << "Scalar addition: " << vcn + ComplexNumber(4.0, -4.0) << endl;

  string svalues[VECTOR_SIZE] = {"alpha", "beta", "gamma", "delta", "epsilon"};
  Vector<string> s(VECTOR_SIZE, svalues);

  cout << s << endl;
  // cout << "Summation of s: " << s.summation() << endl;
  // cout << "Product of s:" << s.product() << endl;
  cout << "Scalar addition (concatentation): " << s + "hello" << endl;

  // return 0 to indicate successful completion from main function
  // and our program
  return 0;
}
