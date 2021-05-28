/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   January 29, 2019
 * @assg   Analysis of Algorithms
 *
 * @description Some code examples related to calculating running time
 *   and asymptotic growth of common code patterns/fragments.
 */
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// we use a global variable to "peek" inside our code fragments
// and count up operations
int operationCount = 0;

/** reset operation count
 * Function to reset the operation counter, called before invoking a code
 * fragment, so we can count up only the operations in that fragment.
 */
void resetOperationCount()
{
  operationCount = 0;
}

/** report algorithm analysis
 * Helper function to report the operation count.  We create and
 * return a string to report the actual operation count, as well
 * as other information.
 *
 * @param n The size (an int) of the input we just ran the past algorithm
 *   fragment on.
 * @param expectedOperationCount The expected number of operations given
 *   the upper/lower bound growth rate O(algorithm).
 * @param algorithmDescription A description of the growth rate of the
 *   algorithm just completed, for display purposes.
 *
 * @returns string Returns a string description/report of the past
 *  algorithm performance.
 */
string reportAlgorithmAnalysis(int n, double expectedOperationCount, string algorithmDescription)
{
  ostringstream out;

  out << "Algorithm O(" << algorithmDescription << ")" << endl
      << "                                 n = " << n << endl
      << "   O() upper bound operation count = " << expectedOperationCount << endl
      << "       actual number of operations = " << operationCount << endl;

  return out.str();
}

/** order 1 (constant time) Algorithm
 * A big-theta(1) (order 1) algorithm.  E.g. an algorithm that takes
 * constant time.
 *
 * @param n The size (an int) of the input.  Not used for a constant
 *   time algorithm.
 *
 * @returns int A result, not really used in these examples
 */
int order1Algorithm(int n)
{
  // The basic operation is an assignment op here, so count it
  int a = 5;
  operationCount++;

  return a;
}

/** order N Algorithm
 * A big-theta(N) (order N) algorithm.  E.g. an algorithm that
 * runs in linear time with respect to input size n.
 * Notice that the assignment is O(1), followed by the loop
 * which executes n times so by rule 4 is O(N).  The
 * time complexity is thus T(n) = O(1) + O(N) which by rule
 * 3 simplifies to O(N) (e.g. we can ignore the less expensive
 * part of the growth).
 *
 * @param n The size (an int) of the input.
 *
 * @returns int A result, not really used in these examples
 */
int orderNAlgorithm(int n)
{
  // assignment operation is an operation
  int sum = 0;
  operationCount++;

  // by rule 4, we loop n times, thus the order of
  // the loop is O(n) * O(1) = O(n)
  for (int iter = 1; iter <= n; iter++)
  {
    // the addition is a O(1) operation
    sum += n;
    operationCount++;
  }

  return sum;
}

/** order 2N Algorithms
 * Example of rule 2 and rule 3,  we have 2 loops of O(N)
 * that run in sequence.  Thus the result is O(2N) opertions.
 * By rule 2, the constant is insignificant, at some point
 * this will be much smaller than even O(n log(n)) algorithm
 * growth.
 *
 * @param n The size (an int) of the input.
 *
 * @returns int A result, not really used in these examples
 */
int order2NAlgorithm(int n)
{
  // assignment operation is an operation
  int sum = 0;
  operationCount++;

  // by rule 4, we loop n times, thus the order of
  // the loop is O(n) * O(1) = O(n)
  for (int iter = 1; iter <= n; iter++)
  {
    // the addition is a O(1) operation
    sum += n;
    operationCount++;
  }

  // a second loop, also of O(n)
  // by rule 3, the overall growth rate is unaffected.  The loops
  // means we do 2N operations, but the growth rate is still linear
  // O(N)
  for (int iter = 1; iter <= n; iter++)
  {
    // the addition is still a O(1) operations
    sum += n;
    operationCount++;
  }

  return sum;
}

/** order N^2 Algorithm
 * Nested loops cause N^2 growth.  This is what rule 4 means by
 * multiplying the growth rates, a loop inside of a loop requires you to
 * multiply their corresponding time functions to determine the resulting
 * growth rate.
 *
 * @param n The size (an int) of the input.
 *
 * @returns int A result, not really used in these examples
 */
int orderNSquaredAlgorithm(int n)
{
  // assignment operation is an operation
  int sum = 0;
  operationCount++;

  // by rule 4, we loop n times, but the inner loop also
  // loops n times, thus the resulting growth rate is
  // O(n) * O(n) = O(n^2)
  for (int outerIter = 1; outerIter <= n; outerIter++)
  {
    // each execution of the outer loop causes the inner
    // loop to execute exactly n times as well
    for (int innerIter = 1; innerIter <= n; innerIter++)
    {
      // the addition is an O(1) constant operation
      sum += n; // probably going to overflow this badly
      operationCount++;
    }
  }

  return sum;
}

/** order 1/2 N^2 Constrained Inner Loop
 * A common pattern in many algorithms is outer loop goes
 * from i = 1 to n, but inner loop only goes from 1 to i.
 * Thus total number of operations is the series
 * sum(1 + 2 + 3 + 4 + .... + n) = n(n + 1) / 2
 *
 * @param n The size (an int) of the input.
 *
 * @returns int A result, not really used in these examples
 */
int orderHalfNSquaredAlgorithm(int n)
{
  // assignment operation is an operation
  int sum = 0;
  operationCount++;

  // by rule 4, we loop n times, but the inner loop also
  // loops n times, thus the resulting growth rate is
  // O(n) * O(n) = O(n^2)
  for (int outerIter = 1; outerIter <= n; outerIter++)
  {
    // each execution of the outer loop causes the inner
    // loop to execute from 1 to outerIter times
    // Makes counting opeations a bit more difficult, but not that
    // difficult
    for (int innerIter = 1; innerIter <= outerIter; innerIter++)
    {
      // the addition is an O(1) constant operation
      sum += n; // probably going to overflow this badly
      operationCount++;
    }
  }

  return sum;
}

/** order log(N) Algorithm
 * Binary search is the prototypical example of log_2(n) growth.  Any time you have
 * a loop that actually increases by some power x, instead of by 1, you will have
 * only log_x growth.  The binary search algorithm has log_2(n) growth because each time
 * through its loop it reduces the size of the items it hasn't searched by 1/2.
 *
 * @param n The size (an int) of the input.
 *
 * @returns int A result, not really used in these examples
 */
int orderLogNAlgorithm(int n)
{
  // assignment operation is an operation
  int sum = 0;
  operationCount++;

  // The loop grows by 2*i each time, not i++, so it is doubling
  // each time.  If it were 3*i we would have log_3(n) growth, etc.
  // i = 1, 2, 4, 8, 16, ... <=n
  for (int iter = 1; iter <= n; iter *= 2)
  {
    sum += n;
    operationCount++;
  }

  return sum;
}

/** order N log(N) Algorithm
 * Also a very common growth rate.  The good sorting algorithms are O(n log(n) ).
 * This happens usually when we have an algorithm with nested loops where the
 * inner loops is O(N) but the outer loop reduces the problem by 1/2 each time,
 * thus by rule 4 we get O(log n) * O(n) = O(n log n)
 *
 * @param n The size (an int) of the input.
 *
 * @returns int A result, not really used in these examples
 */
int orderNLogNAlgorithm(int n)
{
  // assignment operation is an operation
  int sum = 0;
  operationCount++;

  // The outer loop grows by 2*i each time, not i++, so it is doubling
  // each time.  If it were 3*i we would have log_3(n) growth, etc.
  // i = 1, 2, 4, 8, 16, ... <=n
  for (int outerIter = 1; outerIter <= n; outerIter *= 2)
  {
    // but the inner loop is a simple O(N) order loop
    for (int innerIter = 1; innerIter <= n; innerIter++)
    {
      sum += n;
      operationCount++;
    }
  }

  return sum;
}

/** order 2^n (exponential) Algorithm
 * Exponential growth like x^n or factorial growth n! (which is also a type of
 * exponential growth) are usually impractical algorithms for anything
 * but the smallest input size.
 *
 * Usually exponentially growing algorithms are the result of a brute force,
 * naive approach to solving the problem.  For example, in the 8 queens
 * problem, a brute force approach is the following.  You can only have
 * 1 queen per column of the board.  So if you represent the row you place
 * each queen of column in, you end up with a representation like
 * (1, 2, 4, 2, 1, 2, 7, 8), e.g. queen in column 1 is in row 1, queen
 * in column 2 is in row 2, queen in column 3 is in row 4, etc.
 * Then the brute force approach is to generate all possible placements,
 * starting with (1, 1, 1, 1, 1, 1, 1, 1), then (1, 1, 1, 1, 1, 1, 1, 2),
 * etc.  and test each one when after you generate to see if it is
 * a solution.  This actually generates n^n positions that need to
 * be evaluated, which is even larger than 2^n.
 *
 * A common way to get 2^n growth is through a recursive algorithm that
 * breaks the problem of size N into 2 N-1 sized subproblems, then recursively
 * solves those 2 N-1 subproblems.  Using recurrence analysis (see chapter
 * 2 from our supplementary textbook), you can show that this approach is
 * O(2^n).  For example, a naive implementation of the towers of hanoi
 * using a recursive solution will be of this type of algorithm.
 *
 * @param n The size (an int) of the input.
 *
 * @returns int A result, not really used in these examples
 */
int orderExponentialAlgorithm(int n)
{
  // example of 2^n recursive solution
  // base case to halt the recursion
  if (n == 0)
  {
    operationCount++;
    return 1;
  }
  else
  {
    return orderExponentialAlgorithm(n - 1) + orderExponentialAlgorithm(n - 1);
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
  const int n = 100;

  // O(1) or constant time
  resetOperationCount();
  order1Algorithm(n);
  cout << reportAlgorithmAnalysis(n, 1, "1 - constant time") << endl << endl;

  // O(n) or linear time
  resetOperationCount();
  orderNAlgorithm(n);
  cout << reportAlgorithmAnalysis(n, n, "n - linear time") << endl << endl;

  // 2 * O(n) which is still linear growth time
  resetOperationCount();
  order2NAlgorithm(n);
  cout << reportAlgorithmAnalysis(n, n, "2n - linear time") << endl << endl;

  // O(n^2) or quadratic time
  resetOperationCount();
  orderNSquaredAlgorithm(n);
  cout << reportAlgorithmAnalysis(n, pow((double)n, 2), "n^2 - quadratic time") << endl << endl;

  // O(n^2) or quadratic time
  resetOperationCount();
  orderHalfNSquaredAlgorithm(n);
  cout << reportAlgorithmAnalysis(n, 0.5 * n * (n + 1), "1/2 n (n+1) - still quadratic time") << endl << endl;

  // O(log n) or logarithmic time
  resetOperationCount();
  orderLogNAlgorithm(n);
  cout << reportAlgorithmAnalysis(n, log2((double)n), "log n - logarithmic time like binary search") << endl << endl;

  // O(n log n) or logarithmic time
  resetOperationCount();
  orderNLogNAlgorithm(n);
  cout << reportAlgorithmAnalysis(n, n * log2((double)n), "n log n - sorting algorithms") << endl << endl;

  // exponential growth, even 2^n when n=100 is a 31 digit number
  // >>> x = str(2**100)
  // >>> x
  // '1267650600228229401496703205376'
  // >>> len(x)
  // 31
  // which is 10 quintillion.  The following won't work unless you use a much smaller input
  // size n
  int smalln = 10;
  resetOperationCount();
  orderExponentialAlgorithm(smalln);
  cout << reportAlgorithmAnalysis(smalln, pow(2.0, (double)smalln), "2^n - exponential growth") << endl << endl;

  // return 0 to indicate successful completion from main function
  // and our program
  return 0;
}