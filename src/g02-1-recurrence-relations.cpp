/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  CSci 520, Spring 2022
 * @ide    VSCode Server
 * @date   January 24, 2022
 * @assg   Basic Recurrence Relations
 *
 * @description Sedgwick text, basic recurrence relationships from
 *   Formula 2.1 - Formula 2.5
 *
 *   In this code example, we demonstrate code structures that give rise
 *   to the basic recurrence relationship of each formula.  We
 *   also demonstrate empirical measurement of the time to execute
 *   the code, as well as more theoretical analysis of number of 
 *   operations performed for each.
 */
#include <chrono>
#include <iomanip>
#include <iostream>
using namespace std;

// 32 bit int not big enough to hold our counts, so
// use an unsigned 64 bit long int
typedef unsigned long int uint64;


/** formula 2.1
 *
 * Formula 2.1 recurrence relationship is
 *
 *     C_N = C_{N-1} + N, for N \ge 2 with C_1 = 1
 *
 * This relationship will have run time proprotional
 * to N^2/2 and has O(N^2) asymptotic run time.
 *
 * The recurrence relationship shows that we have to process all N
 * elements of input, which eliminats one of the inputs, which
 * we then process to eliminate the next one.
 *
 * @param N The number of inputs (remaining) to be processed.
 */
uint64 formula_2_1(int N)
{
  // we will count up an approximation of the number of operations performed
  // and return as the result of these recurrence relation example functions
  uint64 numops = 0;

  // This relationship means we first process each of the current N elements,
  // implies a loop.
  for (int i = 0; i < N; i++)
  {
    // number of operations is estimated here, we perform 1 op for each input processed
    numops++;
  }

  // result of previous work eliminates one of the items from consideration, so
  // now we need to remove it, perform some operations to process/remove the item
  //numops++;

  // now need to keep performing on remaining N-1 operations, when N=0 we are done
  if (N > 1)
  {
    numops += formula_2_1(N - 1);
  }

  return numops;
}


/** formula 2.2
 *
 * Formula 2.2 recurrence relationship is
 *
 *     C_N = C_{N/2} + 1, for N \ge 2 with C_1 = 1
 *
 * This relationship will have run time proprotional
 * to \log_2 N and is O(\log_2 N)
 *
 * The basic relationship is that we do some constant amount of work
 * which eliminates 1/2 of the input, then we do the same task on
 * the input now reduced in size by 1/2.  This is a binary search
 * for example.
 *
 * @param N The number of inputs (remaining) to be processed.
 */
uint64 formula_2_2(int N)
{
  // we will count up an approximation of the number of operations performed
  // and return as the result of these recurrence relation example functions
  uint64 numops = 0;

  // we do some constant amount of work to reduce the input by 1/2
  numops++;

  // now we can do the same task but on input that has been reduced by 1/2
  if (N > 1)
  {
    // note that this is integer division, so we get the
    // floor of the result here.
    numops += formula_2_2(N / 2);
  }
  
  return numops;
}


/** formula 2.3
 *
 * Formula 2.3 recurrence relationship is
 *
 *     C_N = C_{N/2} + N, for N \ge 2 with C_1 = 0
 *
 * This relationship will have run time proprotional
 * to 2N and is O(N)
 *
 * This recurrence relationship differs from 2.2 in that in order
 * to eliminate 1/2 of the object from consideration, we first have to
 * process all N items, which requires linear time to complete.
 *
 * @param N The number of inputs (remaining) to be processed.
 */
uint64 formula_2_3(int N)
{
  // we will count up an approximation of the number of operations performed
  // and return as the result of these recurrence relation example functions
  uint64 numops = 0;

  // we perform a linear number N operations, which is work to reduce the
  // input items by 1/2 in this relationship
  for (int i = 0; i < N; i++)
  {
    numops++;
  }

  // now we can do the same task but on input that has been reduced by 1/2
  if (N > 1)
  {
    // note that this is integer division, so we get the
    // floor of the result here.
    numops += formula_2_3(N / 2);
  }
  
  return numops;
}


/** formula 2.4
 *
 * Formula 2.4 recurrence relationship is
 *
 *     C_N = 2 C_{N/2} + N, for N \ge 2 with C_1 = 0
 *
 * This relationship will have run time proprotional
 * to N log_2 N and is O(N log_2 N)
 *
 * This recurrence relationship differs from the previous 2.3
 * in that we have to perform some work on both the N/2 redced
 * inputs.  Usually the N operations do some work, then we split the
 * inputs into 1/2 and recursively do the task on the 1/2 sized
 * input sets.  This is typical of good performing search functions,
 * like merge sort and quick sort.
 *
 * @param N The number of inputs (remaining) to be processed.
 */
uint64 formula_2_4(int N)
{
  // we will count up an approximation of the number of operations performed
  // and return as the result of these recurrence relation example functions
  uint64 numops = 0;

  // we perform a linear number N operations, which is work to reduce the
  // input items by 1/2 in this relationship
  for (int i = 0; i < N; i++)
  {
    numops++;
  }

  // now we can do the same task but on input that has been reduced by 1/2,
  // though here we have to do work 2 times, so typically what we have
  // done is split the input up into 1/2 sized chuncks and then we need to perfrom
  // the work again on each of these divided inputs.  For example in merge sort
  // we first copy all values below or above some pivot value to left or right side,
  // thus splitting the input into 2 parts.  We have to iterate over all N items to
  // get them on left or right side.  Then we can call sort recursively on the
  // halves.
  if (N > 1)
  {
    // note that this is integer division, so we get the
    // floor of the result here.
    // perform on 1/2 of the input
    numops += formula_2_4(N / 2);
    // perform taks on other 1/2 of the input
    numops += formula_2_4(N / 2);
  }
  
  return numops;
}


/** formula 2.5
 *
 * Formula 2.5 recurrence relationship is
 *
 *     C_N = 2 C_{N/2} + 1, for N \ge 2 with C_1 = 1
 *
 * This relationship will have run time proprotional
 * to 2N again and is O(N)
 *
 * This recurrence relationship is another example of a linear
 * O(n) relationship.  We have to do some constant amount of work to basically
 * split the input into 2 pieces, then we can do the work on each piece.  The
 * results is basically linear in the size of N.
 *
 * @param N The number of inputs (remaining) to be processed.
 */
uint64 formula_2_5(int N)
{
  // we will count up an approximation of the number of operations performed
  // and return as the result of these recurrence relation example functions
  uint64 numops = 0;

  // we perform a constant amount of work to split the input into 2 parts
  numops++;

  // now we can do the task on the two parts.  When the inputs are split
  // into roughly equal halves, we or performing the same work on N/2 inputs
  // 2 times again
  if (N > 1)
  {
    // note that this is integer division, so we get the
    // floor of the result here.
    // perform on 1/2 of the input
    numops += formula_2_5(N / 2);
    // perform taks on other 1/2 of the input
    numops += formula_2_5(N / 2);
  }
  
  return numops;
}


/** perform tests
 *
 * Given a (function pointer) function that implements a recurrence
 * relation, perform theoretical and empirical tests of the function.
 * This wrapper function runs the empirical tests for some range of
 * values of the N input size.  It records the number of theoretical
 * operations performed and also measure the elapsed wall clock time
 * to get an empirical measure of the performance of the function.
 *
 * @param recurrenceFunction A function pointer to a function that
 *   implements a recurrence relationship.  We expect the function to
 *   take an int N as input, the size of the input to test.  The function
 *   should return an uint64 (unsigned 64 bit int), which is a theoretical
 *   count of the number of operations performed by the function.
 *
 * @returns Nothing is returned explicitly, but a table of the test
 *   results for the given function is created and output to standard
 *   output stream.
 */
void testRecurrenceRelation(uint64 (*recurrenceFunction)(int))
{
  // theoretical tests
  int testN[] = {10, 100, 1'000, 10'000, 100'000};
  //int testN[] = {32, 128, 1024, 16384, 65536, 131072};
  int numTests = 5;
  uint64 numops;

  // empirical wall-clock time tests
  chrono::time_point<std::chrono::system_clock> start;
  chrono::time_point<std::chrono::system_clock> end;
  chrono::duration<double> elapsed_time;
  
  // display header for the result table we will produce on standard
  // output for this function
  cout << setw(7) << right << "N"
       << setw(12) << right << "num ops"
       << setw(12) << right << "time (s)"
       << endl;
  cout << setw(7) << right << "------"
       << setw(12) << right << "-----------"
       << setw(12) << right << "-----------"
       << endl;

  // test recurrence function for inputs of various sizes
  for (int test = 0; test < numTests; test++)
  {
    // obtain test results for this test N input size
    int N = testN[test];
    start = chrono::system_clock::now();
    numops = recurrenceFunction(N);
    end = chrono::system_clock::now();

    // calculate empirical elapsed time
    elapsed_time = end - start;
    
    // display results on recurrencence relation for this N input size
    cout << setw(7) << right << N
	 << setw(12) << right << numops
	 << setw(12) << right << fixed << elapsed_time.count()
	 << endl;
  }
  
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
  // test formula 2.1 recurrence relation
  cout << endl;
  cout << "Recurrence 2.1   N^2/2  -> O(N^2)" << endl;
  testRecurrenceRelation(formula_2_1);

  // test formula 2.2 recurrence relation
  cout << endl;
  cout << "Recurrence 2.2   lg N   -> O(lg N)" << endl;
  testRecurrenceRelation(formula_2_2);

  // test formula 2.3 recurrence relation
  cout << endl;
  cout << "Recurrence 2.3   2N     -> O(N)" << endl;
  testRecurrenceRelation(formula_2_3);


  // test formula 2.4 recurrence relation
  cout << endl;
  cout << "Recurrence 2.4   N lg N -> O(N lg N)" << endl;
  testRecurrenceRelation(formula_2_4);

  // test formula 2.5 recurrence relation
  cout << endl;
  cout << "Recurrence 2.5   2N     -> O(N)" << endl;
  testRecurrenceRelation(formula_2_5);
}
