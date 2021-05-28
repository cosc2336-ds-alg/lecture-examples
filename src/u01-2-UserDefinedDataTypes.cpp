/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   January 14, 2019
 * @assg   User Defined Simple Data Types Video
 *
 * @description Examples for discussion/review about
 *   Enumerated types and the string type.  Also discuss
 *   concept of namespaces.
 */
#include <iostream>
#include <string>

using namespace std;

// define day of the week defined as global named constants
// const int SUNDAY = 0;
// const int MONDAY = 1;
// const int TUESDAY = 2;
// const int WEDNESDAY = 3;
// const int THURSDAY = 4;
// const int FRIDAY = 5;
// const int SATURDAY = 6;

// alternatively define day of week as enumerated type
enum DayOfWeek
{
  SUNDAY,
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY,
};

/** display day of week
 * Example of converting day of week using the global named constants.
 *
 * @param dayOfWeek A DayOfWeek data type, notice the nameof the parameter gives
 *     that we expect a particular type of value, but since the
 *     function accepts int values, it will not prevent us
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
  // Enumerated types are useful to represent a finite set
  // of discrete values.  We can do this ourself, for example
  // by using named constants

  // two drawbacks.  1) there is no compiler check if we are
  // expecting a day of the week.  What if we pass in 7 when
  // expecting one of these constants?  2) similarly this is less
  // readable, if we have a function that takes day of the week,
  // we have to define parameter as int.
  DayOfWeek dayOfWeek = MONDAY;
  cout << "The day of the week is " << convertDayOfWeekToString(dayOfWeek) << endl;

  // dayOfWeek = 7; // nothing prevents us from assigning a bad value
  // cout << "The day of the week is " << convertDayOfWeekToString(7) << endl;

  // But if we convert to an enumerated type, the function and code
  // is more readable because we show our intention with the data type
  // name.  Congratulations, you just created your very own new data type
  // and added it to the C++ language.

  // Sometimes it can be useful/needed to iterate over all of the values of
  // an enumerated data type.  This is an example of where C++ is kinda
  // kludgy and has yucky and verbose syntax.  You can add or increment
  // enumerated types directly, so you have to implicitly convert to an int
  // change it, then static_cast back to the enumerated type.
  for (dayOfWeek = SUNDAY; dayOfWeek <= SATURDAY; dayOfWeek = static_cast<DayOfWeek>(dayOfWeek + 1))
  {
    cout << "iterating through the week, today is " << dayOfWeek << " " << convertDayOfWeekToString(dayOfWeek) << endl;
  }

  //---------------------------------------------------

  // Namespaces are (an attempt) to prevent global declarations of names of functions
  // classes and constants from interfering with one another.

  // The std names space is the C++ standard library namespace.  Things like iostream
  // and many others are defined to be in the std namespace.  Without the
  // using namespace std;  at the top of your file, you need to explicitly indicate
  // which namespace you are referring to if accessing an object inside of a namespace.
  // for example, to use iostream output, you would do
  std::cout << "An example of explicitly stating the namespace of cout" << std::endl;

  // namespaces are really a mechanism for data type and library designers, which
  // is one of the things we are doing in this class.  We could put our enumerated
  // type in our own namespace, for example.

  //----------------------------------------------------

  // The string is not really one of the fundamental types of the C++ language, it
  // is an example of a complex data type.  Strings are really classes (chapter 10)
  // that define an abstract data type for creating and manipulating textual data.
  // You should usually use the high level string type, rather than the old style
  // C array of characters (chapter 8)
  string firstName = "Derek";
  string lastName = "Harter";
  cout << "Hello my name is " << firstName << " " << lastName << endl;

  // operator+ overloads string concatenation
  string s = "Hello my name is " + firstName + " " + "Shawn" + " " + lastName;
  ;
  cout << s << endl;

  //  you can treat a string as an array if you want
  s[0] = 'J';
  cout << s << endl;

  // See table 7-1 (pg 480) of our textbook
  // string is a class, so strings have many member functions you can call on them
  // (again review classes and/or wait till chapter 10 for further explanation).

  // length of string
  cout << "The length of s is " << s.length() << endl;
  ;

  // position and inserting into string
  int pos = s.find("Derek"); // find index of my first name in s
  s.insert(pos, "Banana nana Bo ");
  cout << s << endl;

  // get substring of a string
  cout << s.substr(0, 17) << "Inigio Montoya, you killed my father, prepare to die!" << endl;

  // return 0 to indicate successful completion
  return 0;
}
