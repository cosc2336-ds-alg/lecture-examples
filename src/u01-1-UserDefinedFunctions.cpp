/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   January 14, 2019
 * @assg   Functions Lecture
 *
 * @description Examples for discussion/review about writing and using
 *   functions in C++.
 */
#include <cmath>
#include <cstdlib> // for rand() function
#include <iostream>
using namespace std;

// global variable and constant declarations
int myGlobalVariable = 42;
const double PI = 3.141529;
const double E = 2.7182818; // Euler's constant

// function prototypes
int rollXSidedDiceNTimes(int numberOfSides, int numberOfDiceToRoll);

/** abs
 * A simple user defined function.  Reimplement <cmath> abs
 * function to calculate the absolute value of an integer.
 *
 * @param number An sigend integer, that may be positive or
 *     negative.
 * @returns int The absolute (positive) value of the given
 *     input number.
 */
int abs(int number)
{
  if (number < 0)
  {
    return -number;
  }
  else
  {
    return number;
  }
}

/** Value Parameters Example
 * Example experiment.  What happens if we change the
 * value of value parameters passed to a function?
 *
 * @param param1 An integer, our first parameter which is
 *     passed by value.
 * @param param2 An integer, the second value parameter.
 * @param param3 A double, our third value parameter.
 *
 * @returns void This is an example of a void function.
 *     it does not return any value.
 */
void changeTheValueParameters(int param1, int param2, double param3)
{
  param1 = 99;
  param2 = 88;
  param3 = 77.77;
}

/** Reference Parameters Example
 * Example experiment.  What happens if we change the
 * value of reference parameters passed to a function?
 *
 * @param param1 A characters which is passed by reference.
 * @param param2 A bool value passed in by reference.
 *
 * @returns void This is an example of a void function.
 *     it does not return any value.
 */
void changeTheReferenceParameters(char& param1, bool& param2)
{
  param1 = 'Y';
  param2 = false;
}

int myArray[5] = {00, 10, 20, 30, 40};

/** returnReferenceExample
 * Example of returning a reference as a result from a function.
 *
 * @returns A reference to an int value
 */
int& returnReferenceExample()
{
  return myArray[3];
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
  // C++ libraries provide many predefined functions
  // To use a function in C++, you need to know the
  // name of the function, and what parameters it needs,
  // and what value, if any, it returns.
  double negValue = -3.14159;
  cout << "The absolute value of " << negValue << " is " << abs(negValue) << endl;

  // notice we passed the return value from the function directly
  // to the output.  As textbook says (pg. 341) it is natural
  // to use the value in a calculation, output it (as we just,
  // did) or save the value.

  // save the value
  double absValue = abs(negValue);
  cout << "absValue is " << absValue << endl;

  // use the value in a calculation
  double radius = 3.0;
  double area = abs(negValue) * pow(radius, 2.0);
  area = 3.14159 * radius * radius;

  cout << "The area of a circule of radius " << radius << " is " << area << endl;

  // one of the most fundamental skills in learning to program
  // is breaking down a big problem into smaller problems, so
  // you can solve the small problem with a function you define.

  // To define a function, need the following
  // 1. Give it a name
  // 2. define which parameters you need to give as inputs
  // 3. determine the type of each of the input parameters
  // 4. if the function returns a value, determine the type of the return value

  // the textbook defines its own version of the absoluve
  // value function (this one is for integers)
  int negInt = -2;
  int posInt = abs(negInt);
  cout << "The absolute value using my function of " << negInt << " is " << posInt << endl;

  // another example, using random number library (chapter 5,
  // and Example 6-4.
  // also demonstrate function prototypes
  // play 10 games of craps
  int sum = rollXSidedDiceNTimes(6, 2);
  for (int rollNum = 1; rollNum <= 10; rollNum++)
  {
    sum = rollXSidedDiceNTimes(6, 2);
    cout << "Rolling two 6 sided dice, I got a sum of " << sum << endl;
    if ((sum == 7) || (sum == 11))
    {
      cout << "    natural" << endl;
    }
    if ((sum == 2) || (sum == 3) || (sum == 12))
    {
      cout << "    craps" << endl;
    }
  }

  // value parameters are where a COPY of the
  // value is passed to the function.  value
  // parameters are not changed as a result
  // of calling a function that changes the parameter.
  int valParam1 = 5;
  int valParam2 = 7;
  double valParam3 = 9.9;
  changeTheValueParameters(valParam1, valParam2, valParam3);
  cout << "After call to function <changeTheValueParameters>"
       << " the value of valParam1 is " << valParam1 << " and the value of valParam2 is " << valParam2 << " and the value of valParam3 is "
       << valParam3 << endl;

  // reference parameters pass a REFERENCE to the
  // variable given.  If you change a refernce
  // parameter in the function, the change in the value
  // is seen by the caller.
  char refParam1 = 'X';
  bool refParam2 = true;
  changeTheReferenceParameters(refParam1, refParam2);
  cout << "After call to function <changeTheReferenceParameters>"
       << " the value of refParam1 is " << refParam1 << " and the value of refParam2 is " << boolalpha << refParam2 << endl;

  // it is nonsensical to pass in a constant expression for a
  // reference parameter of a function.  If you do this, the
  // compiler will complain
  // changeTheReferenceParameters('Z', false);

  // variables are local to the scope they are defined in.
  // Scope is defined in a function (inside of braces)
  int exampleOfVariableScope = 5;
  {
    int exampleOfVariableScope = 42;
    cout << "Inner scope, variable value is " << exampleOfVariableScope << endl;
  }
  cout << "Now back to outer scope, variable value is " << exampleOfVariableScope << endl;

  // variables at top of function are global in scope.  Generally you should
  // avoid global variables.
  cout << "The global variable named myGlobaVariable has value " << myGlobalVariable << endl;

  // avoid global variables, but often global named constants are useful and
  // are good programming practice
  cout << "The value of PI is " << PI << " and Euler's constant is " << E << endl;

  // it is an error to try and modify something that is declared as a constant
  // E = 2.6;

  int myInteger = 1;

  myInteger = returnReferenceExample();
  cout << "myIteger is now: " << myInteger << endl;

  myInteger = 50;
  cout << "myInteger is now: " << myInteger << endl;
  cout << "myArray[3] is now: " << myArray[3] << endl;

  returnReferenceExample() = 100;
  cout << "myArray[3] is now: " << myArray[3] << endl;

  // return 0 to indicate successful completion
  return 0;
}

/** roll and sum dice
 * Roll a number of dice with the indicated number of sides.
 * We roll multiple dice, sum up their faces, and return
 * the total sum.
 *
 * @param numberOfSides An int value that indicates how
 *     many sides the dice have we are rolling.
 * @param numberOfDiceToRoll An int value that indicates
 *     the number of dice to roll.
 *
 * @returns int The result sum of rolling the multiple
 *     dice of the indicated number of sides.
 */
int rollXSidedDiceNTimes(int numberOfSides, int numberOfDiceToRoll)
{
  int sum = 0;

  for (int diceNum = 1; diceNum <= numberOfDiceToRoll; diceNum++)
  {
    // simulate rolling single dice with sides from 1 to numberOfSides
    int dice = rand() % numberOfSides + 1;
    sum += dice;
  }

  return sum;
}
