/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   April 20, 2019
 * @assg   C++ Standard Template Library (STL)
 *
 * @description Basics of containters, iterators and algorithms provided
 *   by the C++ standard template library (STL).
 */
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/** Employee class
 * Just a simple example of an employee class, so we can demostrate creating
 * some containers that contain collection of an Employee user defined type.
 */
class Employee
{
private:
  string name;
  int id;
  double salary;

public:
  Employee()
  {
    name = "", id = 0;
    salary = 0.0;
  };
  Employee(string name, int id, double salary)
    : name(name)
    , id(id)
    , salary(salary){};
  double getSalary() const
  {
    return salary;
  };
  bool operator<(const Employee& right) const
  {
    return this->id < right.id;
  };
  friend ostream& operator<<(ostream& out, const Employee& e);
};

/** Employee overload operator<<
 * Overload operator<< to provide output to streams for Employee classes.
 */
ostream& operator<<(ostream& out, const Employee& e)
{
  out << "id: " << e.id << " (" << e.name << " " << setprecision(2) << fixed << e.salary << ")";
  return out;
}

/** Employee salary comparison
 * Example of providing a class with a comparison operator()
 * so that we can organize a priority queue by highest salary.
 */
class EmployeeSalaryComparison
{
public:
  bool operator()(Employee left, Employee right)
  {
    return left.getSalary() < right.getSalary();
  }
};

/** compare double (reverse)
 * Another example of a comparison function. Here we demonstrate a simple
 * function to compare double values.  We order by > so that larger double
 * values are orderd first (lower) than smaller double values.
 */
bool compareDoubleReverse(double left, double right)
{
  return left > right;
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

  // I still find cplusplus.com reference most useful for STL:
  // http://www.cplusplus.com/reference/
  // Another useful site is:
  // https://en.cppreference.com/w/

  //------------------------------------------------------------------------
  // Container adapters provide the fundamentals data types we learn in this
  // class, stack, queue and priority queue (no trees).

  // If you need a stack, just #inclue <stack> and create a stack of the
  // template/type you need
  stack<double> dstack;
  dstack.push(4.5);
  dstack.push(3.8);
  dstack.push(42.0);

  cout << "Is dstack empty? " << boolalpha << dstack.empty() << endl;
  cout << "stack size is now: " << dstack.size() << endl;
  cout << "top item: " << dstack.top() << endl;
  dstack.pop();
  dstack.pop(); // pop top 2 items, only 1 left
  cout << "top item after popping some is: " << dstack.top() << endl;
  dstack.pop();
  cout << "Is dstack empty? " << boolalpha << dstack.empty() << endl;
  // careful, as we discussed a bit, STL classes don't protect you from
  // popping empty stacks/queues
  // the following may crash, or may not but just give you bizarre results
  dstack.pop();
  cout << "stack size: " << dstack.size() << endl;
  cout << endl << endl;

  // likewise can create a basic queue
  queue<string> squeue;
  squeue.push("I'm in line first");
  squeue.push("I'm second");
  squeue.push("I came last");
  cout << "Is squeue empty? " << boolalpha << squeue.empty() << endl;
  cout << "queue size is now: " << squeue.size() << endl;
  cout << "front of the queue: " << squeue.front() << endl;
  squeue.pop();
  cout << "front of queue is now: " << squeue.front() << endl;
  squeue.pop();
  cout << "And finally, front is now: " << squeue.front() << endl;
  squeue.pop();
  cout << "Is squeue empty? " << boolalpha << squeue.empty() << endl;
  cout << endl << endl;

  // priority queue, default is to use < (operator<)
  // BTW, just need the #include <queue> header for priority_queue
  priority_queue<int> mypq;
  mypq.push(30);
  mypq.push(100);
  mypq.push(25);
  mypq.push(40);

  cout << "Popping out elements, will they come out by priority?" << endl;
  while (!mypq.empty())
  {
    cout << "Top item in priority queue: " << mypq.top() << endl;
    mypq.pop();
  }
  cout << endl << endl;

  // we can either overload operator< if we need a priority queue for our own type
  // note the const qualifiers for operator< and operator<< are important, these are
  // expected by top() function...
  priority_queue<Employee> empq;
  empq.push(Employee("Derek Harter", 5, 42.00));
  empq.push(Employee("Jane Programmer", 3, 38.00));
  empq.push(Employee("John Student", 7, 15.00));
  empq.push(Employee("Susie Employee", 6, 58.00));
  cout << "Popping out elements of Employee queue." << endl;
  cout << "operator< defined to order by employee id" << endl;
  while (!empq.empty())
  {
    cout << "Top item in Employee priority queue: " << empq.top() << endl;
    empq.pop();
  }
  cout << endl << endl;

  // You can explicitly define a comparator function instead, if you need
  // to create priority queues for multiple attributes (can't overload operator<
  // multiple times for the same class).
  // Lets do priority by salary this time.  We need a whole new class
  // EmployeeSalaryComparison Also notice the template specification
  // we need to provide the container actually used by the
  // priority_queue which in this case will be a vector containter
  priority_queue<Employee, vector<Employee>, EmployeeSalaryComparison> emsalarypq;

  emsalarypq.push(Employee("Derek Harter", 5, 42.00));
  emsalarypq.push(Employee("Jane Programmer", 3, 38.00));
  emsalarypq.push(Employee("John Student", 7, 15.00));
  emsalarypq.push(Employee("Susie Employee", 6, 58.00));

  cout << "Popping out elements of Employee queue." << endl;
  cout << "EmployeeSalaryComparison compares by salary (bigger salary is highest priority)" << endl;
  while (!emsalarypq.empty())
  {
    cout << "Top item in Employee priority queue: " << emsalarypq.top() << endl;
    emsalarypq.pop();
  }
  cout << endl << endl;

  //------------------------------------------------------------------------
  // The items we just looked at are called "container adapters" in
  // STL.  They are really just abstractions, internally they actually
  // use a concrete container like a vector, dequeu or list.  The
  // actual container used is picked to be most efficient for typical
  // operations of the data type

  // If you understand our discussions about algorithmic efficiency
  // and the differences of linked list vs. array based
  // implementations, the vector, dequeue and list containers should
  // make more sense to you now.

  // A vector contains items in a dynamic array.  Because underlying
  // is an array, items can be accessed in middle effidicnely.  Item
  // insertion at end of array is also efficient, if the vector is not
  // yet full, but insertion in the middle or beginning requires
  // shifting so will be O(n)
  vector<int> vint(5); // the dynamic array underlying the data structure is of size 5
  cout << "vint capacity: " << vint.capacity() << endl;
  cout << "is vint empty? " << boolalpha << vint.empty() << " what is its size? " << vint.size() << endl;

  // notice that the size is 5 even though we didn't add items
  // lets assign some items
  for (int i = 0; i < 5; i++)
  {
    vint[i] = i * i; // set each index to have the square of the index as value
  }

  // we can iterate over vectors using index based iteration
  for (size_t i = 0; i < vint.size(); i++)
  {
    cout << "vint[" << i << "] = " << vint[i] << endl;
  }
  cout << endl;

  // you still need to use and know how to use what are known as iterators.
  // these are actual objects/classes associated with STL containers.  So to
  // iterate over a vector, create the following iterator:
  // notice need to use *it to dereference a pointer, iterators expose some of the
  // cruftiness going on behind the scenes
  for (vector<int>::iterator it = vint.begin(); it != vint.end(); ++it)
  {
    cout << "iterating using old style c++ iterator, found item: " << *it << endl;
  }

  // we can iterate over using the newer range based for loops, which make C++
  // much more like higher level languagues like Python and R
  for (auto num : vint)
  {
    cout << "iterating vint using range based loop, found item: " << num << endl;
  }
  cout << endl;

  cout << endl << endl;

  // so we can iterate over the items in a vector.  What happens if you try and
  // add a sixth item to the container, which is currently full? What do you
  // predict will happen?
  vint.push_back(42);
  cout << "after pushing a 6th item, size: " << vint.size() << endl;
  cout << "  capacity: " << vint.capacity() << endl;

  // notice that basically the vector will double the size.  If we add items
  // past current capacity, it will double again
  vint.push_back(7);
  vint.push_back(8);
  vint.push_back(9);
  vint.push_back(10);
  vint.push_back(11);
  cout << "after pushing a 11th item, size: " << vint.size() << endl;
  cout << "  capacity: " << vint.capacity() << endl;

  // vector, dequeu are much safer than using basic/raw c arrays.  If we
  // reference/allocate an item that is not currently in the vector, the class
  // ignores it which at least doesn't corrupt anything
  vint[1234] = 54;
  cout << "after assiging item 1234, size: " << vint.size() << endl;
  cout << "   capacity: " << vint.capacity() << endl;
  // notice invalid references are quitely ignored

  // vector is basically the array based list implementation we did in this class.

  // a dequeue is also a dynamically allocated array but keeps pointer to first and last
  // item in array.  So insertion to front or back is O(1), but insertion in middle or deletion
  // will be O(n).

  // a list usues a (doubly) linked list rather than a fixed (dynamically allocated) array.
  // thus insertion to front or back is O(1).  A list is not random access, so to access
  // an item in the middle will be more expensive (O(n)) than for the vector or dequeue.

  // The map container provides a basic key/value pair associative container, basically
  // the Dictionary and Hash table data structures we studied.  maps are very useful,
  // and are widely used in high level languages, and you should become familiar
  // with using them.

  // A basic example of using a map to map between an id and an employee
  map<string, Employee> employeeDict;

  employeeDict["Derek Harter"] = Employee("Derek Harter", 5, 42.00);
  employeeDict["Susie Employee"] = Employee("Susie Employee", 6, 58.00);
  employeeDict["John Student"] = Employee("John Student", 7, 16.00);
  employeeDict["Jane Programmer"] = Employee("Jane Programmer", 3, 38.00);

  cout << "size of dictionary/map: " << employeeDict.size() << endl;

  // you can iterate over a dictionary/map.  Most high-level languages
  // use hashing so order is undefined.  However STL uses binary trees,
  // apparently, so will keep in sorted order when you try and iterate
  // over the dictionary/map items
  for (auto it = employeeDict.begin(); it != employeeDict.end(); ++it)
  {
    // it->first is the key and it->second is the value
    cout << "Iterating through employee dict, got key: " << it->first << endl;
    cout << "    got value: " << it->second << endl;
  }
  cout << endl;

  // an example using range based iteration.  In this case you have to know that
  // the map will be returning a pair object, so we need to access the first and
  // second member items to get the key/value from the items being returned.
  for (auto pair : employeeDict)
  {
    cout << "Iterating through employee dict, got key: " << pair.first << endl;
    cout << "    got value: " << pair.second << endl;
  }

  // but the important property is that you can hash/index over the key value you define
  // for your map directly, e.g.
  cout << "Employee record search by name  : " << employeeDict["Derek Harter"] << endl;
  cout << "Another example of index by name: " << employeeDict["John Student"] << endl;

  // actually STL maps are implemented as binary search trees rather
  // than as hash tables in C++ STL.  This is because of difficulties of defining
  // good hashing functions for any arbitrary key type.  Languages like Java and
  // Python are actually able to determine/specify hash function for types and thus use
  // hash tables for dictionary/maps.

  // the unordered_map is actually more comparable to dictionaries you typically find
  // in Java and Python.  It usues a hash table internally.  Thus search and insertion
  // are constant time O(1) operations.  However, as the name implies, if you iterate
  // over the collection it is unordered, so items will be iterated essentially in
  // random order
  unordered_map<string, Employee> employeeUnorderedDict;

  employeeUnorderedDict["Derek Harter"] = Employee("Derek Harter", 5, 42.00);
  employeeUnorderedDict["Susie Employee"] = Employee("Susie Employee", 6, 58.00);
  employeeUnorderedDict["John Student"] = Employee("John Student", 7, 16.00);
  employeeUnorderedDict["Jane Programmer"] = Employee("Jane Programmer", 3, 38.00);

  cout << "size of dictionary/map: " << employeeUnorderedDict.size() << endl;

  // you can iterate over a dictionary/map.  The iteration will be in random
  // ordre for an unordered_map
  for (auto it = employeeUnorderedDict.begin(); it != employeeUnorderedDict.end(); ++it)
  {
    // it->first is the key and it->second is the value
    cout << "Iterating through employee dict, got key: " << it->first << endl;
    cout << "    got value: " << it->second << endl;
  }
  cout << endl;

  // an example using range based iteration.
  for (auto pair : employeeUnorderedDict)
  {
    cout << "Iterating through employee dict, got key: " << pair.first << endl;
    cout << "    got value: " << pair.second << endl;
  }

  // but the important property is that you can hash/index over the key value you define
  // for your map directly, and for an unordered_map these should be O(1)
  // operations on average, e.g.
  cout << "Employee record search by name  : " << employeeUnorderedDict["Derek Harter"] << endl;
  cout << "Another example of index by name: " << employeeUnorderedDict["John Student"] << endl;

  cout << endl << endl;

  //------------------------------------------------------------------------
  // There are many algorithms for thinsk like merging, finding, counting, copying,
  // etc.  We will just look at sort() algorithms here.
  // First of all, actually sort() is defined for a list container, so you can
  // use sort on lists directly
  // you can actually assign a old-style c array to a vector of ints and it does the
  // right thing
  list<int> mylist = {5, 6, 8, 3, 40, 36, 98, 29, 75};
  mylist.sort();
  cout << "After sorting list:" << endl;
  for (auto num : mylist)
  {
    cout << "list item: " << num << endl;
  }
  cout << endl;

  // you can't actually sort vector or dequeue containers directly.  Why not?

  // However we can use sort from the STL algorithms to sort items
  vector<double> mydoubles = {5.5, 8.3, 6.2, 1.2, 8.5, 9.1, 2.6, 4.5};

  // notice we have to use iterators to specify sorting here
  sort(mydoubles.begin(), mydoubles.end());
  cout << "After using sort() STL algorithm on mydoubles:" << endl;
  for (auto num : mydoubles)
  {
    cout << "item: " << num << endl;
  }
  cout << endl;

  // we can also provide our own compare class or function, like we did previously.
  // here since we have a simple vector of doubles, we demonstrate a simple function
  // that takes 2 doubles as input and returns a boolean result.  By returning >
  // rather than < we can do a regerse sort
  sort(mydoubles.begin(), mydoubles.end(), compareDoubleReverse);
  cout << "After using sort() STL algorithm on mydoubles with a compare function:" << endl;
  for (auto num : mydoubles)
  {
    cout << "item: " << num << endl;
  }
  cout << endl;

  return 0;
}
