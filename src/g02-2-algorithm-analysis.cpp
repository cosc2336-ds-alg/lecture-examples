/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  CSci 520, Spring 2022
 * @ide    VSCode Server
 * @date   January 24, 2022
 * @assg   Basic Recurrence Relations
 *
 * @description Sedgwick text, examples of algorithm analysis
 *   using sequential and binary search, section 2.6
 *
 *   A bit more of concrete examples of algorithmic analysis for
 *   some real search algorithms.  Sequential search is O(N)
 *   (linear time), while binary search is O(lg N), but requires
 *   values to be sorted before search is performed.
 */
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
using namespace std;


// globally defined constants
const int NOT_FOUND = -1;


/** generate random values
 *
 * Generate an array of random values.  Values range between 0 and
 * RAND_MAX.  An array and its size is passed in as input to
 * this function, and we initialze the array using random()
 * number generator to generate the values.
 *
 * @param N The size of the array of values to initialize.
 * @param values An array of integer values to be initialized with
 *   random values.
 *
 * @returns void Nothing explicit is returned, but since the array is
 *   passed in by reference, the initialized random values are returned
 *   inside of the passed in array of values.
 */
void generateRandomValues(int N, int values[])
{
  // initialize all values to a random value.  By default rand() returns
  // an int value in the range from 0 to RAND_MAX, where RAND_MAX is usually
  // equivalent to MAX_INT
  for (int idx = 0; idx < N; idx++)
  {
    values[idx] = rand();
  }
}


/** generate random index
 *
 * Generate a random value / index in the range from 0 to N-1
 *
 * @param N The maximum index value to randomly generate.
 *
 * @returns int Returns a random integer index in the range from
 *   0 to N-1 inclusive.
 */
int generateRandomIndex(int N)
{
  // rand() gives a random integer, and taking the remainder gives a
  // random number in the range from 0 to N-1, as required
  return rand() % N;
}


/** sequential search (no early stopping)
 *
 * Perform a basic sequential search on indicated subportion of the
 * array of integer values.  We are given an array of values to search
 * and the value to search for.  We are also given a begin and end index
 * of the array to perform the search within, to make the API equivalent
 * to a binary search.  This implementation does not assume that
 * the array of values being searched is already sorted, so it 
 * cannot test the value and stop once we reach a point where we have
 * passed the value we are searching for.
 *
 * This implementation of a sequential search is an example of an O(N)
 * algorithm, where N = end - begin (the number of values to be searched).
 * In the best case, the value we are looking for might be at index 0, so
 * we return almost immediately.  In the worst case the value is the last
 * value in the array, or the value we are looking for is not in the array
 * and thus the search fails.  In both cases we have to perform N comparisons
 * to find the value or determine the search fails.  On average, given
 * we are searching for values in the array and we are equally likely to
 * find the value at any position, we expect to find the value after N/2
 * comparisons.
 *
 * @param values An array of int values to be searched.
 * @param searchValue The value to be searched for in the array.
 * @param begin The beginning index of the array of values where we should
 *   start our search.
 * @param end The end index (inclusive) of the array of values where we
 *   should absolutely stop searching.
 * @param numops A reference parameter which is used to return the counted
 *   number of comparison operations performed.
 *
 * @returns int Returns the index (between begin and end) where the value is
 *   found.  The index has to be a positive number >= 0 for a successful
 *   search.  We return NOT_FOUND (-1) flag to indicate a failed search.
 */
int sequentialSearch(int values[], int searchValue, int begin, int end, int& numops)
{
  // initialize numops to 0
  numops = 0;
  
  // perform sequential search for the value, exhaustively check all
  // values from begin to end inclusively
  for (int idx = begin; idx <= end; idx++)
  {
    // consider each comparison an "operation", we are about to make
    // a comparison, so update number of operations performed
    numops++;
    
    // if we find what we are searching for, indicate successful search
    // by returning index location of the value we found
    if (values[idx] == searchValue)
    {
      return idx;
    }
  }

  // otherwise if falue was not found, return flag indicating failed search
  return NOT_FOUND;
}


/** sequential search (with early stopping)
 *
 * Perform a basic sequential search on indicated subportion of the
 * array of integer values.  We are given an array of values to search
 * and the value to search for.  We are also given a begin and end index
 * of the array to perform the search within, to make the API equivalent
 * to a binary search.  This implementation does not assume that
 * the array of values being searched is already sorted, so it 
 * cannot test the value and stop once we reach a point where we have
 * passed the value we are searching for.
 *
 * This variation expects (requires) the array to be sorted, and will
 * stop searching as soon as it detects it has passed where the value
 * should be in the array.  This leads to a slight improvement in
 * performance, though if we always search for values in the array, we
 * won't see the performance benefits.
 *
 * @param values An array of int values to be searched.
 * @param searchValue The value to be searched for in the array.
 * @param begin The beginning index of the array of values where we should
 *   start our search.
 * @param end The end index (inclusive) of the array of values where we
 *   should absolutely stop searching.
 * @param numops A reference parameter which is used to return the counted
 *   number of comparison operations performed.
 *
 * @returns int Returns the index (between begin and end) where the value is
 *   found.  The index has to be a positive number >= 0 for a successful
 *   search.  We return NOT_FOUND (-1) flag to indicate a failed search.
 */
int sequentialSearchSorted(int values[], int searchValue, int begin, int end, int& numops)
{
  // initialize numops to 0
  numops = 0;
  
  // perform sequential search for the value, exhaustively check all
  // values from begin to end inclusively
  for (int idx = begin; idx <= end; idx++)
  {
    // consider each comparison an "operation", we are about to make
    // a comparison, so update number of operations performed
    numops++;
    
    // if we find what we are searching for, indicate successful search
    // by returning index location of the value we found
    if (values[idx] == searchValue)
    {
      return idx;
    }

    // early stopping test, if searchValue is greater than current value, it can't
    // be anywhere in the array of values past this point for a sorted array
    numops++;
    if (values[idx] > searchValue)
    {
      return NOT_FOUND;
    }
  }

  // otherwise if falue was not found, return flag indicating failed search
  return NOT_FOUND;
}


/** binary search
 *
 * Perform a binary search.  The binary search assumes (requires)
 * the array of values given to be sorted.  The binary search works
 * by testing the mid point of the current range, and from that 
 * eliminating half of the remaining values because based on the
 * test the value we are searching for will be either before or after
 * the calculated mid point.
 *
 * This is an example of a logarithmic algorithm.  At each iteration,
 * it reduces the number of items to be search by 1/2.  Thus it will
 * perform in O(lg N) time, a substantial improvement over a linear
 * search.
 *
 * @param values An array of int values to be searched.
 * @param searchValue The value to be searched for in the array.
 * @param begin The beginning index of the array of values where we should
 *   start our search.
 * @param end The end index (inclusive) of the array of values where we
 *   should absolutely stop searching.
 * @param numops A reference parameter which is used to return the counted
 *   number of comparison operations performed.
 *
 * @returns int Returns the index (between begin and end) where the value is
 *   found.  The index has to be a positive number >= 0 for a successful
 *   search.  We return NOT_FOUND (-1) flag to indicate a failed search.
 */
int binarySearch(int values[], int searchValue, int begin, int end, int& numops)
{
  // initialize number of operations so we can cout from start of search
  numops = 0;
  
  // as long as begin and end have not crossed, we stil have some range of values
  // that need to be searched
  while (end >= begin)
  {
    // calculate mid point.  Here we rely on integer division to get a valid
    // index between begin and end
    numops += 3; // addition, division and assignment
    int mid = (begin + end) / 2;

    // first test if we have succeeded in the search by seeing if the value at the
    // mid point is the one we are looking for
    numops += 1; // comparison
    if (values[mid] == searchValue)
    {
      return mid;
    }

    // otherwise reduce values still under consideration.  If the searchValue
    // is less than the value at the midpoint, the value must be before the
    // midpoint in the array
    numops += 1; // comparison
    if (searchValue < values[mid])
    {
      numops += 2; // subtraction and assignment
      // update to begin <-> mid-1 of unsearched values
      end = mid - 1;
    }
    // otherwise searchValue > values[mid] so value must be after the midpoint
    else
    {
      numops += 2; // subtraction and assignment
      // update to mid+1 <-> end
      begin = mid + 1;
    }
  }

  // if begin and end cross (e.g. end < begin), then search has failed
  return NOT_FOUND;
}


/** perform tests
 *
 * Given a function (function pointer) that implements a search,
 * perform theoretical and empirical tests of the function.
 * This wrapper function runs the empirical tests for some randomly
 * generated N values.  It records the number of theoretical 
 * operations performed and also measures the elapsed wall clock time
 * to get an empirical measure of the performance of the function.
 *
 * @param searchFunction A function that implements a search algorithm.
 *   We expect the function to have a particular signature
 *   (values[], searchValue, begin, end), and to return the number of
 *   comparison operations performed for the search.
 *
 * @returns Nothing is returned explictly, but a table of the test
 *   results for the given function is created and output to standard
 *   output stream.
 */
void testAlgorithmPerformance(int (*searchFunction)(int[], int, int, int, int&), int M, int N, bool sortValues)
{
  // empirical wall-clock time tests
  chrono::time_point<std::chrono::system_clock> start;
  chrono::time_point<std::chrono::system_clock> end;
  chrono::duration<double> elapsed_time;

  // theoretical tests
  // first generate an array of random values of size N, we dynamically allocate the
  // needed array of int values
  int* values = new int[N];
  generateRandomValues(N, values);
  int totalNumOps = 0;
  int totalFailedSearches = 0;

  // perform M searches on the array of size N.  To be fair to seqential search, we
  // always search for values that are in the array, so that sequential searches end
  // up around N/2 operations on average
  start = chrono::system_clock::now();

  // if using a search that needs values sorted, perform the sort now.
  // note we include the sort time in the empirical time for the search results
  if (sortValues)
  {
    sort(values, values + N);
  }

  // make M searches for numbers that are in the array so are successful
  for (int searchNum = 0; searchNum <= M; searchNum++)
  {
    // pick a value in the array of values at random to search for
    int searchIdx = generateRandomIndex(N);
    int searchValue = values[searchIdx];
    int numops = 0;
    int resultIdx;
    
    // perform the search
    resultIdx = searchFunction(values, searchValue, 0, N-1, numops);
    if (resultIdx == NOT_FOUND)
    {
    //  cerr << "Error: the search function failed to find the expected value" << endl
    //	   << "   searchValue: " << searchValue << endl
    //	   << "   searchIdx  : " << searchIdx << endl
    //	   << "   resultIdx  : " << resultIdx << endl
    //	   << endl;
    //  exit(0);
      totalFailedSearches++;
    }
    totalNumOps += numops;
  }

  // now make another M searches for random numbers, so many (most) will likely
  // end in failed searches.  This should help show effect of failed searches and
  // difference between sequential searches
  for (int searchNum = 0; searchNum <= M; searchNum++)
  {
    // generate a value to search for at random
    int searchValue = rand();
    int numops = 0;
    int resultIdx;

    // perform the search
    resultIdx = searchFunction(values, searchValue, 0, N-1, numops);
    if (resultIdx == NOT_FOUND)
    {
      // count number of failed searches
      totalFailedSearches++;
    }
    totalNumOps += numops;
  }
  
  end = chrono::system_clock::now();

  // calculate empirical elapsed time
  elapsed_time = end - start;
  
  // summarize results as a table
  cout << setw(7) << right << "N"
       << setw(7) << right << "M"
       << setw(12) << right << "num ops"
       << setw(12) << right << "failed"
       << setw(12) << right << "time (s)"
       << endl;
  cout << setw(7) << right << "----"
       << setw(7) << right << "----"
       << setw(12) << right << "-----------"
       << setw(12) << right << "-----------"
       << setw(12) << right << "-----------"
       << endl;
  cout << setw(7) << right << N
       << setw(7) << right << 2 * M
       << setw(12) << right << totalNumOps
       << setw(12) << right << totalFailedSearches
       << setw(12) << right << fixed << elapsed_time.count()
       << endl;
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
  // if we want reproducable result set random seed to a particular
  // value.  If we want different results each time, set random
  // seed to current time
  //srand(42); // select seed to get results you can reproduce
  srand(time(0)); // sets random seed based on current time
  
  // test basic sequential search with no early stopping
  cout << endl;
  cout << "Sequential search (unsorted array)  N/2  -> O(N))" << endl;
  testAlgorithmPerformance(sequentialSearch, 1000, 1'000'000, false);
  
  // test  sequential search on sorted array with early stopping
  cout << endl;
  cout << "Sequential search (sorted array)  N/2?  -> O(N))" << endl;
  testAlgorithmPerformance(sequentialSearchSorted, 1000, 1'000'000, true);
  
  // test binary search on sorted array
  cout << endl;
  cout << "Binary search (sorted array)  lg N  -> O(lg N))" << endl;
  testAlgorithmPerformance(binarySearch, 1000, 1'000'000, true);
  
}
