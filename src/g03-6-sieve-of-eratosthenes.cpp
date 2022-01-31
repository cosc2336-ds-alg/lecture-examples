/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  CSci 520, Spring 2022
 * @ide    VSCode Server
 * @date   January 24, 2022
 * @assg   Quick Find
 *
 * @description Sedgwick text, program 3.5/3.6 Sieve of Eratosthenes.  This 
 *   file uses dynamic memory allocation and asks for number of primes to search
 *   from the command line.
 */
#include <iostream>
using namespace std;

// define global constants, here the number of primes from 2 to N to test/Find
//static const int N = 1000;


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
  // parse command line arguments to determine number of primes to search
  if (argc != 2)
  {
    cerr << "Error: expected command line argument specifying size of prime sieve search" << endl;
    cerr << "Usage: g03-6 N" << endl;
    exit(0);
  }

  // parse N, the size of the sieve from the command line, and dynamically allocate
  // array of booleans of that asked for size.  Be defensive if we can't allocate the
  // request
  int N = atoi(argv[1]);
  bool* primes = new bool[N];;
  if (primes == nullptr)
  {
    cerr << "out of memory" << endl;
    exit(0);
  }
  // initialize all results in primes to true initially, we will set to false
  // as we search and eliminate numbers from being a prime using the sieve
  int i;
  for (i = 2; i < N; i++)
  {
    primes[i] = true;
  }

  // perform the sieve, for each number, set multiples of the number to be false, since
  // those will have this number as a divisor and thus can't be prime
  for (i = 2; i < N; i++)
  {
    // if the number is a prime, all multiples of this numer are not primes
    if (primes[i])
    {
      // iterate over multiples of i
      for (int j = i; (j * i < N) and (j * i > 0); j++)
      {
	primes[i * j] = false;
      }
    }
  }

  // show results of the sieve/search
  cout << "Found the following primes:";
  for (i = 2; i < N; i++)
  {
    if (primes[i])
    {
      cout << " " << i;
    }
  }
  cout << endl;
}
