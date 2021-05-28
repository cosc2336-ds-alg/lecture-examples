/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   January 18, 2019
 * @assg   C++ Pointers Video
 *
 * @description Examples for discussion/review about defining
 *   and using Pointer variables in C++
 */
#include <iostream>
#include <sstream> // for string streams
#include <string>

using namespace std;

/** student record
 * A simple struct/record to hold information about a student.
 */
struct StudentType
{
  string name;
  int cwid;
  double gpa;
  char grade;

  StudentType* next;
};

/** StudentType tostring
 * A helper function to represent student as a string, so we can
 * display a student record easily on cout.
 *
 * @returns string A string representation of the student information.
 */
string tostring(StudentType& student)
{
  ostringstream output;

  output << "Name: " << student.name << endl
         << "   cwid : " << student.cwid << endl
         << "   GPA  : " << student.gpa << endl
         << "   grade: " << student.grade << endl;
  return output.str();
}

/** student record
 * A simple student type, but this time as a class, to illustrate
 * using pointers to class member functions as well as class
 * variables
 */
class StudentTypeClass
{
private:
  string name;
  int cwid;
  double gpa;
  char grade;

public:
  StudentTypeClass(string name, int cwid, double gpa, char grade);
  void setName(string name);
  string getName();
  string tostring();
};

/** StudentTypeClass constructor
 * Constructor for StudentTypeClass to initialize all private member
 * variables.
 *
 * @param name The name of the student as a string.
 * @param cwid The student campus wide id
 * @param gpa  The current student gpa as a double
 * @param grade The current student grade, a char
 */
StudentTypeClass::StudentTypeClass(string name, int cwid, double gpa, char grade)
{
  this->name = name;
  this->cwid = cwid;
  this->gpa = gpa;
  this->grade = grade;
}

/** StudentTypeClass name setter
 * Setter function to set the student name.
 *
 * @param name The new name for the student as a string.
 */
void StudentTypeClass::setName(string name)
{
  this->name = name;
}

/** StudentTypeClass name getter
 * Getter function to get and return the student name.
 *
 * @returns string The name of this student.
 */
string StudentTypeClass::getName()
{
  return this->name;
}

/** StudentTypeClass to string
 * Create a string representation of this student record and
 * return it.
 *
 * @returns string A string representation of this student.
 */
string StudentTypeClass::tostring()
{
  ostringstream output;

  output << "Name: " << this->name << endl
         << "   cwid : " << this->cwid << endl
         << "   GPA  : " << this->gpa << endl
         << "   grade: " << this->grade << endl;
  return output.str();
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
  // Declaring pointer variables ------------------------------------------
  // The *, in addition to meaning multiplication, indicates a pointer
  // and dereferencing a pointer
  int* p;

  // A pointer in C/C++ is a memory address.  But it points to memory
  // that is expected to hold or be interpreted as some particular
  // data type.  Previous points to an integer somewhere in memory (or
  // it will).  We can point to data of any type in memory.
  char* c;

  // style note, note that the following
  int *x, y;

  int* z;
  int someIntValue = 5;
  z = &someIntValue;
  *z = 22;

  cout << "The value of z is now: " << *z << " and also the int value: " << someIntValue << endl;

  // does not make both pointers, only x is a pointer, y is a regular
  // int.  textbook suggests this style:
  // int *x, *y;

  // but I prefer to always declare variables, especially pointer
  // variables, only 1 at a time (1 per line
  // int* x;
  // int* y;

  // also another style issue, most shops require prepending ptr to
  // all pointer names, thus
  // int p;
  // int* ptrP = & p;

  // Initializing, address of operator -----------------------------------
  // and dereferencing pointer variables
  // For a pointer to be useful, we have to point it to something.
  int myInt;
  int* ptrInt = &myInt;

  myInt = 22;

  cout << "myInt has value: " << myInt << endl;
  cout << "ptrInt pointing to value: " << *ptrInt << endl;

  // we can repoint pointers to other things, for example
  int anotherInt = 42;
  ptrInt = &anotherInt;
  cout << "ptrInt now pointing to value: " << *ptrInt << endl;

  // you can use a pointer not only to read a value pointed to in memory,
  // but to also write a new value into it
  *ptrInt = -42;
  cout << "myInt: " << myInt << " anotherInt: " << anotherInt << " ptrInt value: " << *ptrInt << endl;

  // you can also have 2 or more pointers point to the same thing, and you
  // can copy an address from one pointer to another.
  int* ptrAlsoInt;
  // notice whatever ptrInt address is now copied to ptrAlsoInt, they now
  // both point to same thing, which is currently anotherInt
  ptrAlsoInt = ptrInt;

  *ptrAlsoInt = 9999;
  cout << "myInt: " << myInt << " anotherInt: " << anotherInt << " ptrInt value: " << *ptrInt << " ptrAlsoInt value: " << *ptrAlsoInt
       << endl;

  // we can actually use the address of operator and pointer variables to see
  // the real memory address being used and referenced.  For example, what
  // is the address in memory of anotherInt?
  cout << "The address in memory of anotherInt is: " << &anotherInt << endl;
  cout << "The contents of ptrInt is: " << ptrInt << endl;
  cout << "The contents of ptrAlsoInt is: " << ptrAlsoInt << endl;

  // show address changes if pointing to different variable
  ptrAlsoInt = &myInt;
  cout << "The address of myInt is: " << &myInt << endl;
  cout << "The address ptrAlsoInt holds is: " << ptrAlsoInt << endl << endl;

  cout << "size of integer is: " << sizeof(myInt) << endl;

  // pointers to classes, structs -----------------------------------------
  // Conceptually pointing to a user defined type is no different
  // than pointing to a simple built-in type in C++.  In fact, all of the
  // above examples pointing to an integer help illustrate how pointers work,
  // but in real code you almost never do anything like that to point to a single
  // simple value.  However, pointers are very useful to set up complex data
  // structures when used to point to classes and structs.

  // Before we get to that, lets look at a pointer to a simple struct, and
  // add one more operator, the member access/derefernce operator.
  // We have created a StudentType structure.  Lets create an instance
  // of one, and a pointer to it.
  StudentType student;
  StudentType* ptrStudent = &student;

  // recall, accessing a member variable to initialize we use the . operator
  student.name = "Jane Programmer";

  // we can access member items in struct the same way using the pointer, we
  // have to dereference first, and because of order of precedence, we have
  // to use () to force dereference before member access, e.g.
  (*ptrStudent).cwid = 12345678;

  // because using pointers to point to structs and classes is so useful, and
  // we often need to dereference and access a member item of something we
  // are pointing to, C and C++ added the -> operator for doing the simulatenous
  // dereference and access of a member item of a class/struct
  ptrStudent->gpa = 3.8;
  ptrStudent->grade = 'A';

  // show that the assignments worked
  cout << tostring(student) << endl;

  // notice, tostring() takes a (reference to) a student, so if we
  // dereference ptrStudent, it is like we are passing in a student
  // so the result is the same
  cout << tostring(*ptrStudent) << endl;

  // The -> dereference and member access operator also works on classes, and
  // in particular on class member functions.  For a class, we usually don't
  // have publically accessible member variables, but we do have public member
  // functions.
  StudentTypeClass anotherStudent("Joe Moe", 87654, 2.9, 'C');
  StudentTypeClass* ptrAnotherStudent = &anotherStudent;
  // whops got name wrong
  ptrAnotherStudent->setName("Joe Schmoe");
  cout << "Another student name: " << ptrAnotherStudent->getName() << endl;
  cout << "The whole student record: " << endl;
  cout << ptrAnotherStudent->tostring() << endl;

  // Pointers for a linked list -------------------------------------------
  // Finally, we can use pointer to create complex data structures.  You may have
  // noticed that in the struct, there was a self-referential pointer defined.
  // We can use this mechanism to create simple linked lists.  For example:
  StudentType student2;
  student2.name = "John Jingleheimer";
  student2.cwid = 2468;

  StudentType student3;
  student3.name = "Susie Sophomore";
  student3.cwid = 5432;

  student.next = &student2;
  student2.next = &student3;
  student3.next = NULL;

  int studentNum = 1;
  ptrStudent = &student;
  while (ptrStudent != NULL)
  {
    cout << "Student number: " << studentNum << endl;
    cout << tostring(*ptrStudent) << endl;
    ptrStudent = ptrStudent->next;
    studentNum++;
  }

  // return 0 to indicate successful completion
  return 0;
}