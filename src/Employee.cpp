/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   January 18, 2019
 * @assg   C++ Hashing and Dictionaries
 *
 * @description A simple Employee record to use with containers.
 */
#include "Employee.hpp"
#include <iostream>
using namespace std;

/**
 *
 */
ostream& operator<<(ostream& out, const Employee& e)
{
  out << e.tostring();
  return out;
}
