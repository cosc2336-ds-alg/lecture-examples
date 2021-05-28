/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   January 18, 2019
 * @assg   C++ Hashing and Diectionaries examples
 *
 * @description A simpley Employee record for use in containers.
 */
#include <iostream>
#include <sstream>
#include <string>

#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

using namespace std;

/**
 *
 */
class Employee
{
private:
  int employeeId;
  string name;
  float salary;

public:
  Employee(){};
  Employee(int employeeId, string name, float salary)
    : employeeId(employeeId)
    , name(name)
    , salary(salary){};
  string tostring() const
  {
    stringstream out;
    out << "[Employee id: " << employeeId << ", name: " << name << ", salary: redacted]";
    return out.str();
  }

  friend ostream& operator<<(ostream& out, const Employee& e);
};

#endif // EMPLOYEE_HPP
