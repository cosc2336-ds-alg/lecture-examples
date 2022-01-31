/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  CSci 520, Spring 2022
 * @ide    VSCode Server
 * @date   January 24, 2022
 * @assg   Quick Find
 *
 * @description Sedgwick text, program 3.1 function definition
 */
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;


// function prototypes or function declarations
int lg(int n);

/** main
 *
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
  // example of using our hand built log function.  Construct a table of logarithms
  // of some big values of n
  for (int n = 1000; n <= 1000000000; n *= 10)
  {
    cout << lg(n) << " "
	 << setw(7) << setprecision(4) << fixed << log2(n) << " "
	 << n << endl;
  }
  
  // return 0 to indicate successful program completion
  return 0;
}

/** log (base 2) of N
 *
 * Use a brute force method to calculate the log of parameter n
 * in base 2. We repeatedly divide N by 2 using integer division until
 * the result is 0.  The number of divisions required is the log base 2
 * of the parameter n
 *
 * @param n An integer value that we want to find the log_2 of.
 *
 * @returns int Returns the log base 2 of the input parameter n we are given.
 */
int lg(int n)
{
  // determine number of times n can be divided by 2
  int i;
  for (i = 0; n > 0; i++, n /= 2)
  {
    // do nothing, the index i is incremented and n is dividied by
    // 2 in the update portion of the for loop
  }

  // the number of divisions, which will be counted by the loop variable i,
  // is the log_2 of the value n we were given
  return i;
}
