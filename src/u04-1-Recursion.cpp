/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   January 18, 2019
 * @assg   C++ Recursion
 *
 * @description Recursion definitions, writing recursive functions,
 *   function call stack, recursion and iteration.
 */
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

/** find maximum in list (iterative)
 * Find the maximum value in a given list and return it.
 *
 * @param list[] An array of integers to determine largest value within.
 * @param begin  The beginning index to search for maximum within list.
 * @param end    The end index to search for maximum within list.
 *
 * @returns
 */
int largestIterative(int list[], int begin, int end)
{
  int largestSoFar = list[begin];
  for (int index = begin + 1; index <= end; index++)
  {
    if (list[index] > largestSoFar)
    {
      largestSoFar = list[index];
    }
  }
  return largestSoFar;
}

/** find maximum in list (recursive)
 * Find the maximum value in a given list and return it.
 *
 * @param list[] An array of integers to determine largest value within.
 * @param begin  The beginning index to search for maximum within list.
 * @param end    The end index to search for maximum within list.
 *
 * @returns
 */
int largestRecursive(int list[], int begin, int end)
{
  // base case
  if (begin == end)
  {
    return list[begin];
  }
  // general case
  else
  {
    int mid = (begin + end) / 2;

    return max(largestRecursive(list, begin, mid), largestRecursive(list, mid + 1, end));
  }
}

/** power (recursive)
 * Find the power of x^y.  Here y is an integer power that
 * we are rasing x to, but x can be real valued number
 * double).
 *
 * This function demonstrates a recursive solution.
 *
 * @param x A double, the value to be raised to a power.
 * @ param y An int, the power to raise x to
 *
 * @result double The result of raising x^y
 */
double power(double x, int y)
{
  // base case for y = 0
  if (y == 0)
  {
    return 1.0;
  }
  // base case for y = 1
  else if (y == 1)
  {
    return x;
  }
  // general case, for positive y > 1
  else if (y > 1)
  {
    return x * power(x, y - 1);
  }
  // general case, for negative y < 0
  else if (y < 0)
  {
    return 1.0 / power(x, -y);
  }
  else // should never get here
  {
    cerr << "<power> Error: should not reach this point, no case for"
         << " y = " << y << endl;
    assert(false);
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
  cout << "Test find maximum iterative: --------------------------" << endl;
  int values[5] = {3, 8, 2, 9, 7};

  cout << "The largest value in whole list is: " << largestIterative(values, 0, 4) << endl;

  cout << "The largest value from 0 to 2 list is: " << largestIterative(values, 0, 2) << endl;

  cout << "Test find maximum recursive: --------------------------" << endl;
  int b, e;
  int res;
  b = 0;
  e = 0;

  cout << "Test base case, b=" << b << " e=" << e << endl;
  res = largestRecursive(values, b, e);
  cout << "   The largest value is: " << res << endl;
  assert(res == 3);

  b = e = 4;
  cout << "Test base case, b=" << b << " e=" << e << endl;
  res = largestRecursive(values, b, e);
  cout << "   The largest value is: " << res << endl;
  assert(res == 7);

  b = e = 2;
  cout << "Test base case, b=" << b << " e=" << e << endl;
  res = largestRecursive(values, b, e);
  cout << "   The largest value is: " << res << endl;
  assert(res == 2);

  b = 0;
  e = 4;
  cout << "Test general case, b=" << b << " e=" << e << endl;
  res = largestRecursive(values, b, e);
  cout << "   The largest value is: " << res << endl;
  assert(res == 9);

  b = 0;
  e = 3;
  cout << "Test general case, b=" << b << " e=" << e << endl;
  res = largestRecursive(values, b, e);
  cout << "   The largest value is: " << res << endl;
  assert(res == 9);

  cout << "Test power recursive: --------------------------" << endl;
  double x;
  int y;

  double resp;

  x = 5.0;
  y = 0;
  cout << "Test raise to 0 base case" << endl;
  resp = power(x, y);
  cout << "   the result is: " << resp << endl;
  assert(resp == 1.0);

  x = 5.0;
  y = 1;
  cout << "Test raise to 1 base case" << endl;
  resp = power(x, y);
  cout << "   the result is: " << resp << endl;
  assert(resp == 5.0);

  x = 123.123;
  y = 1;
  cout << "Test raise to 1 base case" << endl;
  resp = power(x, y);
  cout << "   the result is: " << resp << endl;
  assert(resp == 123.123);

  x = 5.0;
  y = 2;
  cout << "Test raise general case for y is positive" << endl;
  resp = power(x, y);
  cout << "   the result is: " << resp << endl;
  assert(resp == 25.0);

  x = 2.0;
  y = 10;
  cout << "Test raise general case for y is positive" << endl;
  resp = power(x, y);
  cout << "   the result is: " << resp << endl;
  assert(resp == 1024.0);

  x = 2.0;
  y = -3;
  cout << "Test raise general case for y is negative" << endl;
  resp = power(x, y);
  cout << "   the result is: " << resp << endl;
  assert(resp == (1.0 / 8.0));

  return 0;
}