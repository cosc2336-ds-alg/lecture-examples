/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   January 18, 2019
 * @assg   C++ Dynamic Memory Video
 *
 * @description Dynamic memory allocation, dynamic variables
 *   and memory management issues in C++
 */
#include <iostream>
#include <sstream> // string streams

using namespace std;

/** ListType abstract data type
 * Example of a ListType that can grow dynamically.  We are still using
 * a fixed array of values, but if the list grows bigger than can hold,
 * we dynamically grow our array of memory we are using instead of giving
 * an error.
 *
 * @param size The size or number of items currently contained in the list
 * @param item A base address of an array that holds the actual items
 * contained in the list.
 */
// We will allocate memory in increments of this size.
const int ALLOCATION_INCREMENT = 10;

class ListType
{
private:
  int size;      // the current number of items in the list, e.g. the list size
  int allocSize; // the actual amount of memory allocation we currently have
  int* item;     // The base address of current list of items.

public:
  ListType();  // default class constructor
  ~ListType(); // class destructor

  int getSize();
  int getAllocSize();
  void appendItem(int value);
  string tostring();
};

/** ListType default constructor
 * Initialize as an empty list.  Initially we have no memory
 * allocated, and the size (and allocation size) are 0.
 */
ListType::ListType()
{
  size = allocSize = 0;
  item = NULL;
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
  cout << "This list object went out of scope. size: " << size << endl;

  // be a good memory manager, free up memory we have allocated
  if (item != NULL)
  {
    delete[] item;
  }
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

/** ListType allocSize getter
 * Getter method to access and return current size of memory allocation.
 *
 * @returns int The current size of our allocation
 */
int ListType::getAllocSize()
{
  return allocSize;
}

/** ListType append
 * Append an item to the end of the list.
 * This function causes the list to grow.
 *
 * @param value The item to append to the end of the list.
 */
void ListType::appendItem(int value)
{
  // determine if we have filled up our current allocation and thus
  // must first grow our allocated space
  if (size >= allocSize)
  {
    int newAllocSize = allocSize + ALLOCATION_INCREMENT;
    cout << "<ListType::appendItem()> LOG: growing list from current allocation size " << allocSize << " to new allocation size "
         << newAllocSize << endl;

    // first allocate space for new items
    int* newItem = new int[newAllocSize];

    // now copy current item into new item values
    for (int index = 0; index < size; index++)
    {
      newItem[index] = item[index];
    }

    // we are done using the old allocation, free it
    // IMPORTANT: don't leak memory!
    if (item != NULL)
    {
      delete[] item;
    }

    // now start using the new items
    item = newItem;
    allocSize = newAllocSize;
  }

  item[size] = value;
  size++;
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

  output << "list size: " << size << " alloc size: " << allocSize << " items: [";
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
  // Dynamic variables ----------------------------------------------------
  // The power behind pointers come from using them to work with dynamically
  // allocated memory.
  // Dynamic variables are those that are created during program execution.
  // As opposed to static defined variables.
  // Using new to allocate a single variable
  int* p = new int;
  *p = 42;

  cout << "The value of the dynamically allocated int is: " << *p << endl;

  // using new to allocate an array or a block of variables
  const int NUM_INTS = 16;
  int* q = new int[NUM_INTS];
  int index;

  // q is actually a pointer to (tbe base address) of an array of 16 characters.
  // e.g. you can use it like an array of ints, e.g. int q[16];
  for (index = 0; index < NUM_INTS; index++)
  {
    q[index] = (index * 2) + 1; // 1 3 5 7 9...
  }

  for (index = 0; index < NUM_INTS; index++)
  {
    cout << "q[" << index << "] = " << q[index] << endl;
  }

  // Why is this better than just declaring
  int r[NUM_INTS];
  r[5] = 8;

  // well for one, trying using a variable specified at runtime
  int numInts = 0;
  cout << "How many ints should I use? ";
  // cin >> numInts;

  // This shouldn't compile.  if it does compile, it is very unsafe and buggy
  // int s[numInts];

  // Ah but there is a solution.  If we dynamically allocate at runtime, everything
  // is fine.  A better\ example in a bit
  int* s = new int[numInts];

  // Memory that is dynamically allocated should be freed up if/when it is no longer
  // being used, using the delete operator
  // free up a single variable
  delete p;

  // free up a dynamic array of variables
  delete[] s;

  // dynamic arrays and pointers ------------------------------------------
  // The above example using a dynamic array might have been surprising to
  // you.
  int* myDynamicArray;
  myDynamicArray = new int[NUM_INTS];

  int myStaticArray[NUM_INTS];

  for (index = 0; index < NUM_INTS; index++)
  {
    myStaticArray[index] = (2 * index) + 1;
    myDynamicArray[index] = (2 * index) + 1;
  }

  for (index = 0; index < NUM_INTS; index++)
  {
    cout << "myStaticArray[" << index << "] = " << myStaticArray[index] << "  myDynamicArray[" << index << "] = " << myDynamicArray[index]
         << endl;
  }
  cout << endl << endl;

  int* ptrArray;

  // you can use pointers and pointer arithemetic to index into an array,
  // we start at base address, which is index [0], and by incrementing 3 time
  // we are now pointing to element at index [3]
  ptrArray = myStaticArray; // notice no & address of operator
  ptrArray++;
  ptrArray++;
  ptrArray++;
  *ptrArray = 9999;

  for (index = 0; index < NUM_INTS; index++)
  {
    cout << "myStaticArray[" << index << "] = " << myStaticArray[index] << "  myDynamicArray[" << index << "] = " << myDynamicArray[index]
         << endl;
  }
  cout << endl << endl;

  // likewise, can also use addition, e.g.
  ptrArray = myDynamicArray; // copy base address into pointer
  *(ptrArray + 8) = 9999;    // equivalent to myDynamicArray[8] = 9999

  for (index = 0; index < NUM_INTS; index++)
  {
    cout << "myStaticArray[" << index << "] = " << myStaticArray[index] << "  myDynamicArray[" << index << "] = " << myDynamicArray[index]
         << endl;
  }
  cout << endl << endl;

  // this is how arrays passed to functions work, passing base address, and
  // since it is a pointer, it is passing by reference, and the references
  // change the original caller.
  // return 0 to indicate successful completion

  // An example to try and show why dynamic memory allocation is powerful
  // Revisit our ListType object.
  ListType myList;

  // initially empty
  cout << "myList size = " << myList.getSize() << " allocSize = " << myList.getAllocSize() << endl;

  // lets append an item
  myList.appendItem(42);
  cout << "myList: " << endl << myList.tostring() << endl;

  // append 10 more items to fill up current allocation
  for (index = 0; index < 9; index++)
  {
    myList.appendItem((index * 2) + 1);
  }
  cout << "myList: " << endl << myList.tostring() << endl;

  // and append another, to show it dynamically grows again
  myList.appendItem(42);
  cout << "myList: " << endl << myList.tostring() << endl;

  return 0;
}
