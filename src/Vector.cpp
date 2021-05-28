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
#include "Vector.hpp"
#include "ComplexNumber.hpp"
using namespace std;

/** Vector constructor
 * The common constructor for a Vector object.  We take a number
 * of items, and the actual values of the items as input, and we
 * copy these values to be the items in our vector.
 *
 * @param numItems The number of items we are initializing this
 *   Vector with.
 * @param initItmes An array of the actual items to initialize this
 *   Vector with.
 */
template<class T>
Vector<T>::Vector(int numItems, T initItems[])
{
  this->numItems = numItems;

  // dynamically allocate enough memory to hold a block of
  // T items
  items = new T[numItems];

  // copy the items into ourself
  for (int index = 0; index < numItems; index++)
  {
    items[index] = initItems[index];
  }
}

/** Vector destructor
 * The Vector type allocates an array of items dynamically when it
 * is constructed.  Be goo stewards of memory and make sure this
 * is freed up when this Vector goes out of scope.
 */
template<class T>
Vector<T>::~Vector()
{
  // cout << "<Vector::~Vector()> LOG: destructor entered" << endl;
  delete[] items;
}

/** Vector summation
 * Perform summation of a series.  We sum all of the items in
 * this Vector and return the resulting sum.
 *
 * @returns int Retuns the summation of this Vector series.
 */
/*
template <class T>
T Vector<T>::summation()
{
  T sigma;

  // need to be careful, can't just start out the sum at 0
  sigma = items[0];

  for (int index = 1; index < numItems; index++)
  {
    sigma += items[index];
  }

  return sigma;
}
*/

/** Vector product
 * Perform a product of a series.  We multiply each item
 * in this Vector series to the next item in the series.
 * The result of this chain of products of the Vector/series
 * items is the result of this function.
 *
 * @returns int Returns the product of this Vector series.
 */
/*
template <class T>
T Vector<T>::product()
{
  T pi;

  // need to be careful, can't just start out the sum at 0
  pi = items[0];

  for (int index = 1; index < numItems; index++)
  {
    pi *= items[index];
  }

  return pi;
}
*/

/** Vector difference
 * Perform a series difference on this Vector items.
 * We subtract each item in this Vector series from
 * the previous item in the series.  The result of this
 * chain of differences of the Vector/series
 * items is the result of this function.
 *
 * @returns int Returns the difference of this Vector series.
 */
/*
template <class T>
T Vector<T>::difference()
{
  T diff;

  // need to be careful, can't just start out the sum at 0
  diff = items[0];

  for (int index = 1; index < numItems; index++)
  {
    diff -= items[index];
  }

  return diff;
}
*/

/** Vector overload operator+
 * Perform vector + scalar addition.  The scalar value
 * is added to each item in this Vector.  This results
 * in a new Vector object, which is created and
 * returned by this function.
 *
 * @param value The scalar value (an int) we are adding
 *   to each item of this Vector.
 *
 * @returns Vector& Returns a reference to a newly
'*   created Vector which holds the result of the
 *   scalar addition.
 */
template<class T>
Vector<T>& Vector<T>::operator+(T value)
{
  // we dynamically create a new vector for the result of
  // the vector + scalar addition
  Vector<T>* result = new Vector<T>(numItems, items);

  // we add the scalar value to the new result vector
  for (int index = 0; index < numItems; index++)
  {
    result->items[index] += value;
  }

  // and we return this new resulting vector
  return *result;
}

/** Vector overload operator*
 * Perform vector * scalar multiplication.  The scalar
 * value is multiplied to each item in this Vector.
 * This results in a new Vector object, which is
 * created and returned by this function.
 *
 * @param value The scalar value (an int) we are
 *   multiplying to each item of this Vector.
 *
 * @returns Vector& Returns a reference to a newly created
 *   Vector which holds the result of the scalar
 *   addition.
 */
/*
template <class T>
Vector<T>& Vector<T>::operator*(T value)
{
  // we dynamically create a new vector for the result of
  // the vector * scalar multiplication
  Vector<T>* result = new Vector<T>(numItems, items);

  // we add the scalar value to the new result vector
  for (int index = 0; index < numItems; index++)
  {
    result->items[index] *= value;
  }

  // and we return this new resulting vector
  return *result;
}
*/

/** Vector overload operator<
 * Perform a vectorized boolean less than < comparison.
 * The value is compared to each item in this Vector,
 * and the boolean result is returned as a new
 * vector of int values (1 representing true, 0 false).
 *
 * @param value The scalar value (an int) we are
 *   doing a boolean comparison to each item in
 *   this Vector.
 *
 * @returns Vector& Returns a reference to a newly created
 *   Vector which holds the (boolean) result of the
 *   scalar boolean less than comparisons.
 */
template<class T>
Vector<bool>& Vector<T>::operator<(T value)
{
  // we dynamically create a new vector for the result of
  // the vector boolean operation
  bool* boolItems = new bool[numItems];

  // we add the scalar value to the new result vector
  for (int index = 0; index < numItems; index++)
  {
    boolItems[index] = items[index] < value;
  }

  // dynamically create the result to return
  Vector<bool>* result = new Vector<bool>(numItems, boolItems);

  // and we return this new resulting vector
  delete[] boolItems;
  return *result;
}

/** Vector to string
 * Represent this Vector as a string for display purposes.
 * This is a const function, so this object is guaranteed to not
 * be changed as a result of calling this function.
 *
 * @returns string A string representation of the items
 *   of this Vector is created and returned.
 */
template<class T>
string Vector<T>::tostring() const
{
  ostringstream out;

  out << "<Vector> numItems: " << numItems << "  [";

  if (numItems >= 1)
  {
    out << boolalpha << items[0];
  }

  for (int index = 1; index < numItems; index++)
  {
    out << ", " << items[index];
  }
  out << "]";

  return out.str();
}

/** Vector overload operator<<
 * This is a friend function of the Vector class to overload
 * the output stream operator<<.  We simply reuse the
 * member tostring() method to do our actual work, and insert
 * the string into the given output stream.
 *
 * @param out The output stream we should insert the Vector
 *   representation into.
 * @param aVector A reference to a Vector object that we
 *   need to insert the string representation of into the
 *   given output stream.
 *
 * @returns ostream& Returns reference to original output
 *   stream, but after we have inserted infrmation about
 *   aVector into the output stream.
 */
template<class U>
ostream& operator<<(ostream& out, const Vector<U>& aVector)
{
  out << aVector.tostring();
  return out;
}

/**
 * @brief Cause specific instance compilations
 *
 * This is a bit of a kludge, but we can use normal make dependencies
 * and separate compilation by declaring template class
 * Vector<needed_type> here of any types we are going to be
 * instantianting with the template.
 *
 * https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
 * https://isocpp.org/wiki/faq/templates#separate-template-class-defn-from-decl
 */
template class Vector<bool>;
template class Vector<int>;
template class Vector<string>;
template class Vector<ComplexNumber>;

template ostream& operator<<<bool>(ostream&, const Vector<bool>&);
template ostream& operator<<<int>(ostream&, const Vector<int>&);
template ostream& operator<<<string>(ostream&, const Vector<string>&);
template ostream& operator<<<ComplexNumber>(ostream&, const Vector<ComplexNumber>&);
