/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   January 18, 2019
 * @assg   C++ Stacks Implementation video
 *
 * @description Introduction to Stacks.
 *   A Stack ADT.
 */
#include "Stack.hpp"
#include <iomanip>
#include <iostream>
#include <sstream> // string streams
#include <string>

using namespace std;

//-------------------------------------------------------------------------
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
  // Test array based stack -----------------------------------------------
  cout << "---------- Testing array based stack ----------------------------" << endl;
  AStack<string> aStack;

  // test isEmpty
  cout << boolalpha << "Is aStack empty? " << aStack.isEmpty() << endl;
  cout << aStack << endl;
  cout << endl;

  // test push some items.
  aStack.push("Derek");
  aStack.push("Susan");
  aStack.push("Alan");

  // test top
  cout << aStack << endl;
  cout << "My top item: " << aStack.top() << endl;
  cout << boolalpha << "Is aStack empty? " << aStack.isEmpty() << endl;
  cout << endl;

  // test pop
  aStack.pop();
  aStack.pop();
  cout << aStack << endl;
  cout << "My top item: " << aStack.top() << endl;
  cout << endl;

  // test top from empty stack
  aStack.pop();
  cout << boolalpha << "Is aStack empty? " << aStack.isEmpty() << endl;
  cout << aStack << endl;
  try
  {
    aStack.top();
  }
  catch (EmptyStackException emptyStackObj)
  {
    cout << "Caught expected EmptyStackException: " << endl << emptyStackObj.what() << endl << endl;
  }

  // test pop from empty stack
  try
  {
    aStack.pop();
  }
  catch (EmptyStackException emptyStackObj)
  {
    cout << "Caught expected EmptyStackException: " << endl << emptyStackObj.what() << endl << endl;
  }

  // Test list based stack ------------------------------------------------
  cout << "---------- Testing list based stack ----------------------------" << endl;
  LStack<double> lStack;

  // test isEmpty
  cout << boolalpha << "Is lStack empty? " << lStack.isEmpty() << endl;
  cout << lStack << endl;
  cout << endl;

  // test push some items.
  lStack.push(4.2);
  lStack.push(-3.0e-15);
  lStack.push(42e42);

  // test top
  cout << lStack << endl;
  cout << "My top item: " << lStack.top() << endl;
  cout << boolalpha << "Is lStack empty? " << lStack.isEmpty() << endl;
  cout << endl;

  // test pop
  lStack.pop();
  lStack.pop();
  cout << lStack << endl;
  cout << "My top item: " << lStack.top() << endl;
  cout << endl;

  // test top from empty stack
  lStack.pop();
  cout << boolalpha << "Is lStack empty? " << lStack.isEmpty() << endl;
  cout << lStack << endl;
  try
  {
    lStack.top();
  }
  catch (EmptyStackException emptyStackObj)
  {
    cout << "Caught expected EmptyStackException: " << endl << emptyStackObj.what() << endl << endl;
  }

  // test pop from empty stack
  try
  {
    lStack.pop();
  }
  catch (EmptyStackException emptyStackObj)
  {
    cout << "Caught expected EmptyStackException: " << endl << emptyStackObj.what() << endl << endl;
  }

  return 0;
}
