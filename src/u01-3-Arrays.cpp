/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   January 14, 2019
 * @assg   C++ Arrays Video
 *
 * @description Examples for discussion/review about declaring,
 *   accessing and using simple 1-dim arrays of values in C/C++
 */
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

// global declared constants and data types
enum DayOfWeek
{
  SUNDAY,
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY
};

/** display day of week
 * Example of converting day of week using the global named constants.
 *
 * @param dayOfWeek A DayOfWeek data type, notice the nameof the
 *     parameter gives that we expect a particular type of value, but
 *     since the function accepts int values, it will not prevent us
 *     from passing in an invalid value.
 *
 * @returns string This function returns the day of the week
 *     as a string, suitable for printing out.
 */
string convertDayOfWeekToString(DayOfWeek dayOfWeek)
{
  string dayOfWeekString = "unknown";

  switch (dayOfWeek)
  {
  case SUNDAY:
    dayOfWeekString = "Sunday";
    break;
  case MONDAY:
    dayOfWeekString = "Monday";
    break;
  case TUESDAY:
    dayOfWeekString = "Tuesday";
    break;
  case WEDNESDAY:
    dayOfWeekString = "Wednesday";
    break;
  case THURSDAY:
    dayOfWeekString = "Thursday";
    break;
  case FRIDAY:
    dayOfWeekString = "Friday";
    break;
  case SATURDAY:
    dayOfWeekString = "Saturday";
    break;
  }

  return dayOfWeekString;
}

/** initialize array of doubles
 * Given an array of doubles, and its size, initialize the array
 * to the indicated value.  This function illustrates use of default
 * values, if no value is specified, the array is initialized to 0.0
 * by default.
 *
 * @param size The number of elements (int) in the array to initialize.
 *     This function initializes all elements from 0 up to size-1
 *     in the array.
 * @param array An array of type double, passed in by reference, whose
 *     elements will be initialized by this function.
 * @param value A double value which is the value the array elements
 *     will be initialized to.  By default we initialize the values of
 *     the array to 0.0.
 *
 * @returns void Nothing explicitly returned, but implicitly we
 *     modify the values of array to initialize them on return.
 */
void initializeArrayOfDoubles(int size, double array[], double value = 0.0)
{
  for (int index = 0; index < size; index++)
  {
    array[index] = value;
  }
}

/** display array of doubles
 * Given an array of doubles, display its contents on the cout
 * stream.  The size of the array and the array itself are passed in
 * to this function.  This function does not change the values in the
 * array of doubles, only reads them, so the array is declared as
 * a const input parameter.
 *
 * @param size The number of elements (int) in the array to display.
 *     This function displays all elements from 0 up to size-1
 *     in the array.
 * @param array An array of type double, passed in by reference, whose
 *     elements will be initialized by this function.  We do not
 *     modify the elements of the array, thus the array is declared
 *     const.
 *
 * @returns void Nothing explicitly returned, but as a side effect
 *     the values of the array are written to the cout stream.
 */
void displayArrayOfDoubles(int size, const double array[])
{
  for (int index = 0; index < size; index++)
  {
    cout << "array[" << index << "] = " << array[index] << endl;
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
  //--------------------------- Declaring and Using
  // We can't do very much with a simple variable that holds only
  // a single value.

  // Arrays are a collection of a fixed number of components ALL
  // OF THE SAME DATA TYPE (they are homogeneous)
  const int MY_DOUBLES_SIZE = 10; // used in examples of processing arrays
  double myDoubles[MY_DOUBLES_SIZE];
  int myIntegers[5];
  DayOfWeek myDaysOfWeek[42];

  // Arrays in C/C++ language are 0 INDEXED.  An array of size 5,
  // like myIntegers, has first element in index [0] and last in
  // index [5 -1] = index [4]
  myIntegers[0] = 10; // The first element is in index 0
  myIntegers[4] = 33; // The fifth element is in index 4

  myDaysOfWeek[33] = MONDAY;

  // you must be very careful about accessing arrays beyond their declared bounds
  // myIntegers[5] = 42; // ruh roh danger shaggy
  // cout << "Beyond my size, the value is " << myIntegers[5555] << endl;

  // you can assign values individually like above (write to array)
  // and you can read out values using same syntax
  cout << "My first value is " << myIntegers[0] << " and my last value is " << myIntegers[4] << endl;

  cout << "The day of the week I set " << convertDayOfWeekToString(myDaysOfWeek[33]) << endl;

  // also you can use values in calculations, anywhere you would use a simple
  // variable
  int mySum = myIntegers[0] + myIntegers[4];
  cout << "The sum of the first and last integers in myIntegers is " << mySum << endl;

  // ruh roh, don't ever read uninitialized variables,
  // result is undefined, can't count on initialized to 0
  cout << "What is my second value? " << myIntegers[1] << endl;
  cout << "What happens if access uninitialized day of week? " << convertDayOfWeekToString(myDaysOfWeek[0]) << endl;

  //------------------------- initialize, print, sum, min
  // The normal way to process an array, is to use iteration (a loop)
  // To access and perform some operation on each element of an array
  // Notice since arrays go from 0 to size-1, the index of our loops start
  // at 0 and go to index < size (which only goes up to size-1)

  // initialize myDoubles
  int index;
  for (index = 0; index < MY_DOUBLES_SIZE; index++)
  {
    myDoubles[index] = abs(15.0 - pow(index - 5.0, 2.0));
  }

  // access all values to ouput them
  for (index = 0; index < MY_DOUBLES_SIZE; index++)
  {
    cout << "myDoubles[" << index << "] = " << myDoubles[index] << endl;
  }

  // process all elements to perform a calculation.  Here find the sum of
  // the squares of all of the values.
  double sumOfSquares = 0.0; // need a variable to hold running result
  for (index = 0; index < MY_DOUBLES_SIZE; index++)
  {
    sumOfSquares += pow(myDoubles[index], 2.0);
  }
  cout << "The sum of the squares of the values in myDoubles is " << sumOfSquares << endl;

  // search for the largest element, here we keep track of the largest
  // we have seen so far, and we start by saying the first element at
  // index 0 is the largest so far, and start by comparing element 1.
  // So notice that we loop through here starting at index 1 instead
  // of 0 as before
  int maxIndex = 0; // before we start, largest we have seen is in index 0
  for (index = 1; index < MY_DOUBLES_SIZE; index++)
  {
    // if current value is larger, remember it as the new
    // biggest value we have seen
    if (myDoubles[index] > myDoubles[maxIndex])
    {
      maxIndex = index;
    }
  }
  cout << "The largest value in myDoubles is at index " << maxIndex << " and has a value of " << myDoubles[maxIndex] << endl;

  // The textbook notes that as of C++0x
  // (https://en.wikipedia.org/wiki/C%2B%a2B#Standardization) C++ will
  // support range-based for statements.  These are much more like how
  // iteration over arrays and lists are done in higher-level
  // languages, we may use these when talking about STL
  // redo the print/display example using range-based iteration
  cout << "Using range based iteration" << endl;
  for (double& aDouble : myDoubles)
  {
    cout << "   processing value " << aDouble << endl;
  }

  //------------------------- arrays as parameters to functions
  // you can pass a whole array to a function arrays are always PASSED
  // BY REFERENCE (and you do not specify the & syntax) You could use
  // a global named constant in functions to determine the size of the
  // array, but this is discouraged.  Lets look at a function to
  // initialize an array of doubles.
  initializeArrayOfDoubles(MY_DOUBLES_SIZE, myDoubles);

  // lets make another function to display an array of doubles, so we don't
  // have to repeat ourself in looking at the result.
  cout << "Displaying all of the contents of myDoubles, after initializing:" << endl;
  displayArrayOfDoubles(MY_DOUBLES_SIZE, myDoubles);

  // writing functions that take arrays by passing in the array size
  // along with the array gives more flexibility, and makes the
  // function be self-contained. For example, lets only initialize the
  // first 5 values now...
  initializeArrayOfDoubles(5, myDoubles, 42.42);
  cout << "Displaying all of myDoubles, after initializing some elements:" << endl;
  displayArrayOfDoubles(MY_DOUBLES_SIZE, myDoubles);

  //--------------------------- old C-style strings using arrays of characters
  // To process textual data origianlly in C, arrays of characters
  // were used.  Two special parts of the language for arrays of
  // characters, the null terminator for C-style strings was used by
  // functions to determine the string size, and sting constants could
  // be used to initialize a C-style character array to be used as a
  // string
  char name[16]; // just an array of char type, like we have been using

  // could initialize like this
  name[0] = 'D';
  name[1] = 'e';
  // etc.  but that is tedious
  // cout << name;

  // could use statement declaration array initializers,
  char myName[] = {'D', 'e', 'r', 'e', 'k', '\0'}; // notice the null terminator

  // but string constants will initialize a character array (and will
  // add in the null terminator for your).
  char myOtherName[] = "Harter";

  // cout streams can be sent c-style character arrays, and they know what to do
  cout << "Hello, my name is " << myName << " " << myOtherName << endl;

  // but you should always use the new sting class if you can, it is
  // more powerful, for example arrays can't be overloaded to provide
  // concatenation
  char myFullName[25];
  // myFullName = myName + myOtherName; // won't work, for char arrays, or any C array
  // cout << myFullName;

  // return 0 to indicate successful completion
  return 0;
}