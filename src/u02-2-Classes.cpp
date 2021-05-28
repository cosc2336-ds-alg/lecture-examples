/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   January 14, 2019
 * @assg   C++ Classes Video
 *
 * @description Examples for discussion/review about defining
 *   and using Classes in C++, including example of
 *   data abstraction.
 */
#include <climits> // for MAX_INT
#include <iostream>
#include <sstream> // string stream, for making a string
#include <string>

using namespace std;

/** ListType abstract data type
 * A continuation of a more complete implementation of an abstract
 * list data type.  We encapsulate the variables we need in order
 * to maintain a conceptual list as private member variables.  We
 * expose an interface by declaring public member functions that can be
 * used to create and manipulate a list.  For simplicty of illustration,
 * we will continue to use a list of integers for our list ADT.
 *
 * @param size The size or number of items currently contained in the list
 * @param item An array that holds the actual items contained in the list.
 */
// maximum number of items we can hold in list.  using fixed size of memory
// for now, later when we learn about dynamic memory, we can do better.
const int MAX_LIST_SIZE = 100;
// flag indicates a failed search for item in list.  Technically -INT_MAX
// could be a valid value in our list, so this isn't really safe.  We should
// really implement an exception instead
const int ITEM_NOT_FOUND = -INT_MAX;

class ListType
{
private:
  int size;                // the current number of items in the list, e.g. the list size
  int item[MAX_LIST_SIZE]; // The actual items contained in the list.

public:
  ListType();                      // default class constructor
  ListType(int size, int value);   // initialize empty list
  ListType(int size, int items[]); // construct list from an array of ints
  ~ListType();                     // class destructor

  int getSize();
  int getItem(int index);
  void setItem(int index, int value);
  void appendItem(int value);
  void prependItem(int value);
  int findItem(int value);
  string tostring();
};

/** ListType default constructor
 * Initialize as an empty list
 */
ListType::ListType()
{
  size = 0;
}

/** ListType init constructor
 * Construct a list and initialize it to a given size.  All values
 * in list are initialized to the indicated value, which is
 * 0 by default.
 *
 * @param size An int, the size the newly constructed list should be.
 * @param value An int, the default value to initialize list items
 *   to be.   By default, items are initialized to 0.
 */
ListType::ListType(int sz, int value = 0)
{
  size = sz;

  for (int index = 0; index < size; index++)
  {
    item[index] = value;
  }
}

/** ListType array constructor
 * Construct a list and initialize it using values passed
 * in from an array of integers.
 *
 * @param size An int, the size the array of values we are
 *   initializing list with, and this will be the resulting
 *   size of the list we initialize.
 * @param values An array of integer values that we are to
 *   copy into our list to initialize it.
 */
ListType::ListType(int sz, int values[])
{
  size = sz;

  for (int index = 0; index < size; index++)
  {
    item[index] = values[index];
  }
}

/** ListType array destructor
 * The class destructor.  This is not too useful now, but later
 * when we allocate memory dynamically in an ADT, this is where
 * we should free up any memory we allocate, in order to avoid
 * memory leakage.  There can be only 1 destructor, and it
 * has no parameters.
 */
ListType::~ListType()
{
  cout << "This list object when out of scope. size: " << size << endl;
}

/** ListType size getter
 * Getter method to access and return current list size.
 *
 * @returns int The current size of the list
 */
int ListType::getSize()
{
  return size;
}

/** ListType item getter
 * Getter method to get a particular indexed item from
 * the list.
 *
 * @param index The index of the item to access and
 *   return.
 *
 * @returns int The index'th item from this list.
 */
int ListType::getItem(int index)
{
  return item[index];
}

/** ListType item setter
 * Setter method to set (overwrite) the list item
 * at indicated index.
 *
 * @param index The index of the item to access and
 *   return.
 * @param value The value to set the index'th item
 *   to.
 */
void ListType::setItem(int index, int value)
{
  // we don't do all the error checking we should in this
  // example ADT.  But what if trying to set an item that
  // doesn't exist?
  if ((index < 0) || (index >= size))
  {
    cout << "<ListType::setItem()> ERROR: index does not exist"
         << " index = " << index << " size = " << size << endl;
    return;
  }

  // otherwise, should be a valid index,
  item[index] = value;
}

/** ListType append
 * Append an item to the end of the list.
 * This function causes the list to grow.
 *
 * @param value The item to append to the end of the list.
 */
void ListType::appendItem(int value)
{
  // some minimal error checking
  if (size >= MAX_LIST_SIZE)
  {
    cout << "<ListType::appendItem()> ERROR: no more space available to append item" << endl;
    return;
  }

  item[size] = value;
  size++;
}

/** ListType prepend
 * Insert an item at the front of the list.
 * This function causes the list to grow.
 *
 * @param value The item to prepend to the front of the list.
 */
void ListType::prependItem(int value)
{
  // some minimal error checking
  if (size >= MAX_LIST_SIZE)
  {
    cout << "<ListType::appendItem()> ERROR: no more space available to append item" << endl;
    return;
  }

  // have to first shift all items up 1
  // we start at end and work down, because it is safe to
  // shift the last item up by 1 index
  for (int index = size - 1; index >= 0; index--)
  {
    item[index + 1] = item[index];
  }

  // now that all items shifted up by 1 index, can safely put
  // new value into index 0
  item[0] = value;
  size++;
}

/** ListType find
 * Find first instance of a particular value in our list.
 * This function returns the index of where the first instance
 * of the indicated value was located.
 *
 * @param value The item to search for.
 *
 * @returns int Returns the index where item was found in the list, or
 *   else returns a flag ITEM_NOT_FOUND if the search fails
 */
int ListType::findItem(int value)
{
  // perform a linear search through the items in the list
  for (int index = 0; index < size; index++)
  {
    // if we find the value, return the index where it was
    // found immediately
    if (item[index] == value)
    {
      return index;
    }
  }

  // if we reach here, we searched the whole list unsuccessfully
  // for the value.  So we return an error flag
  return ITEM_NOT_FOUND;
}

/** ListType tostring
 * Represent current state of list as a string suitable
 * for display on an output stream like cout.
 *
 * @returns string This member function returns the state of
 *   this list represented as a string.
 */
string ListType::tostring()
{
  ostringstream output;

  output << "list size: " << size << " items: [";
  for (int index = 0; index < size; index++)
  {
    output << item[index] << ", ";
  }
  output << "]";
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
  // Creating classes, public vs. private ---------------------------------
  // Classes and structs are really the same in C++.  Everything we showed with
  // a struct applies to a class.
  // You can even use public and private for struct.  Only difference, by default
  // everything in a struct is public unless declared otherwise.  But for a class
  // it is the reverse, everything is private unless declared public.
  ListType emptyList; // default constructor
  cout << "Using default constructor to create empty list, emptyList size: " << emptyList.getSize() << endl;

  // Accessing and using class ---------------------------------------------
  // Use the init constructor
  ListType list1(5, 42);
  cout << "Using init constructor, list1 size: " << list1.getSize() << endl;
  // it is illegal to try and access a private member directly
  // cout << "list1 size: " << list1.size << endl;

  // Implementation of member functions (getter and setter) ----------------
  // test the setItem setter and getItem getter method
  list1.setItem(3, 5);
  cout << "Get the 3rd item of list1: " << list1.getItem(3) << endl;
  cout << "Get the 4th item of list1, should have been inited to 42: " << list1.getItem(4) << endl;
  cout << "Example of ADT safety, try and set an invalid item" << endl;
  list1.setItem(50, 6);

  // it is often useful to be able to represent an Object/ADT state
  // as a string, so we can quickly print it out.
  cout << "Test tostring() list1:" << endl << "   " << list1.tostring() << endl;

  // All things we talked about for struct same for class ----------------
  // we can assign classes to one another
  ListType anotherList = list1;
  cout << "Contents of anotherList are:" << endl << "   " << anotherList.tostring() << endl;

  // test out the appendItem() member function
  list1.appendItem(16);
  list1.appendItem(25);
  list1.appendItem(36);
  cout << "After appending 3 additional items list1:" << endl << "   " << list1.tostring() << endl;

  // test out the prependItem() member functions
  list1.prependItem(49);
  list1.prependItem(64);
  list1.prependItem(81);
  cout << "After prepending 3 additional items list1:" << endl << "   " << list1.tostring() << endl;

  // test out findItem() member function
  int index;

  index = list1.findItem(42);
  cout << "The first occurance of 42 in list1 was at index: " << index << endl;

  index = list1.findItem(36);
  cout << "The first occurance of 36 in list1 was at index: " << index << endl;

  index = list1.findItem(1234);
  cout << "The first occurance of 1234 in list1 was at index: " << index << endl;
  if (index == ITEM_NOT_FOUND)
  {
    cout << "   This is actually the ITEM_NOT_FOUND flag, so last search failed" << endl;
  }

  // just another exmaple of a constructor, this one can initialize list
  // using a passed in array
  int someValues[] = {5, 10, 15, 20, 25, 30, 35, 40};
  ListType list2(8, someValues);
  cout << "Testing array constructor, list2:" << endl << "   " << list2.tostring() << endl;

  // constructors and destructors -----------------------------------------------
  // When instances of our ListType go out of scope, the destructor
  // is automatically called.

  // return 0 to indicate successful completion
  return 0;
}