/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   February 2, 2019
 * @assg   Vector
 *
 * @description An example class to show class templates.  This class
 *   will apply a series of operations on provided array of elements
 *   of template type T
 */
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#ifndef VECTOR_HPP
#define VECTOR_HPP

/** Series calculations
 *
 */
template<class T>
class Vector
{
private:
  int numItems;
  T* items; // An array of dynamically allocated items

public:
  // constructors and destructors
  Vector(int numItems, T initItems[]);
  ~Vector();

  // series summation, product, difference
  // T summation();
  // T product();
  // T difference();

  // vector op scalar operations
  Vector<T>& operator+(T value);
  // Vector<T>& operator*(T value);
  Vector<bool>& operator<(T value);

  // overload output stream function (needs to be a friend function)
  // for display purposes
  string tostring() const;
  template<typename U>
  friend ostream& operator<<(ostream& out, const Vector<U>& aVector);
};

#endif // VECTOR_HPP
