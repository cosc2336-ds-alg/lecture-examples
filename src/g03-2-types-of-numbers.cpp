/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  CSci 520, Spring 2022
 * @ide    VSCode Server
 * @date   January 24, 2022
 * @assg   Quick Find
 *
 * @description Sedgwick text, program 3.2 Types of numbers
 */
#include <cmath>
#include <iomanip>
#include <iostream>
#include <cstdlib>
using namespace std;

// define a new (alias) for the int type
typedef int Number;


/** random number
 *
 * Generate and return a random number.  Really a wrapper around the
 * standard library rand() function.  Number returned is in the range
 * from 0 to MAX_INT.
 *
 * @returns Number Returns a randomly generated number
 */
Number randNum()
{
  return rand();
}

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
  // example of command line argument parsing.  We expect the first command
  // line argument to be the number N of values we want to generate
  // We add in a usage message and bit of defensive programming
  if (argc != 2)
  {
    cerr << "Error did not specify number of values to generate." << endl << endl;
    cerr << "Usage: g03-2 N" << endl;
    exit(0);
  }

  // parse the first command line argument, convert it to an integer
  int n = atoi(argv[1]);

  // calculate mean and standard deviation of the values "on the fly" using summation
  // expressions
  float sumOfValues = 0.0;
  float sumOfSquares = 0.0;

  cout << "Values: ";
  for (int i = 0; i < n; i++)
  {
    // generate random number
    Number x = randNum();
    cout << x << ", ";
    
    // we keep a running sum of the values divided by n
    sumOfValues += float(x) / n;

    // likewise keep a running sum of square of the values divided by n
    sumOfSquares += pow(float(x), 2.0) / n;
  }
  cout << endl;

  cout << "     Avg: " << fixed << sumOfValues << endl;
  cout << " Std dev: " << fixed << sqrt(sumOfSquares - pow(sumOfValues, 2.0)) << endl;
  
}
