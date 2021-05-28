/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Fall 2019
 * @ide    Visual Studio Community 2017
 * @date   November 19, 2019
 * @assg   C++ Hashing and Dictionaries Video
 *
 * @description Introduction to Dictionary ADT.  Also using
 *   hashing to create efficient O(1) dictionary lookups.
 */
#include "Dictionary.hpp"
#include "Employee.hpp"
#include <iostream>
#include <sstream>

using namespace std;

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
  // an example, a dictionary using string keys and float values
  ADictionary<string, float> dict1;

  dict1.insert("Derek", 42.0);
  cout << "Dictionary size is now: " << dict1.getSize() << endl;

  dict1.insert("Tom", 10.0);
  dict1.insert("Carol", 22.0);
  dict1.insert("Susan", 55.0);
  dict1.insert("John", 33.0);
  cout << "Dictionary size is now: " << dict1.getSize() << endl;

  cout << "Search for Susan: " << dict1.find("Susan") << endl;
  cout << "Search for Derek: " << dict1.find("Derek") << endl;
  cout << "Search for BadKey: " << dict1.find("BadKey") << endl;

  cout << "Remove Tom and Susan" << endl;
  dict1.remove("Tom");
  dict1.remove("Susan");
  cout << "Dictionary size is now: " << dict1.getSize() << endl;

  cout << endl << endl;

  // of course the values can, and usually are, much more complex.
  // like an Employee struct
  ADictionary<int, Employee> dict2;

  Employee e1(123123, "Derek Harter", 50.0);
  dict2.insert(123123, e1);
  Employee e2(454454, "Carol Brown", 30.0);
  dict2.insert(454454, e2);
  Employee e3(888777, "Tom Green", 75.0);
  dict2.insert(888777, e3);
  cout << "Dictionary 2 size is now: " << dict2.getSize() << endl;

  cout << "Search for employee 888777: " << dict2.find(888777) << endl;
  cout << "Search for employee 123123: " << dict2.find(123123) << endl;

  // return 0 to indicate successful completion of program
  return 0;
}
