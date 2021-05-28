/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   January 14, 2019
 * @assg   C++ Structs Video
 *
 * @description Examples for discussion/review about using
 *   struct in C++.  Declaring, accessing, assignment, passing
 *   struct to functions, and arrays of struct.
 */
#include <iostream>
#include <string>

using namespace std;

/** HouseStyle
 * Valid house styles for our real estate listings.
 */
enum HouseStyle
{
  CAPE_COD,
  COUNTRY,
  COLONIAL,
  VICTORIAN,
  TUDOR,
  RANCH,
  OTHER,
};

/** HouseStyle to string
 * Helper function for HouseStyle user defined data type to convert
 * the enumerated type to a more human readable string for output.
 *
 * @param style A HouseStyle enumerated type we need to convert.
 * @returns string The human-readable string representation of the
 *   HouseStyle.
 */
string styleToString(HouseStyle style)
{
  switch (style)
  {
  case CAPE_COD:
    return "Cape Cod";
  case COUNTRY:
    return "Country";
  case COLONIAL:
    return "Colonial";
  case VICTORIAN:
    return "Victorian";
  case TUDOR:
    return "Tudor";
  case RANCH:
    return "Ranch";
  case OTHER:
  default:
    return "Error - Unsupported Style";
  }
}

/** HouseType
 * Collect information describing a particular house, like for a database
 * of real estate listings.
 */
struct HouseType
{
public:
  HouseStyle style;
  string address;
  int numOfBedrooms;
  int numOfBathrooms;
  int numOfCarsGarage;
  int yearBuilt;
  int finishedSquareFootage;
  double price;
  double tax;
};

/** set house style
 * Given a house (HouseType) as input, attempt to set the house style.
 * This function demonstrates that struct are passed by value.
 *
 * @param house A HouseType struct, the house we are to set the style of.
 * @param style A HouseStyle enumerated type, the new value for our house
 *   style.
 */
void setHouseStyle(HouseType house, HouseStyle style)
{
  house.style = style;
  cout << "Inside of <setHouseStyle()> style is now: " << styleToString(house.style) << endl;
}

/** set house price
 * Given a house (HouseType) as input, attempt to set the price of the
 * house.  This function demonstrates that struct are passed by value.
 *
 * @param house A HouseType struct, the house we are to set the style of.
 *   Notice we pass this parameter by reference, so changes made to
 *   members of this function will be refelected in caller after calling.
 * @param price A double, the new price of the house.
 */
void setHousePrice(HouseType& house, double price)
{
  house.price = price;
  cout << "Inside of <setHousePrice()> price is now: $" << house.price << endl;
}

/** ListType
 * An abstract list data type.  This data type encapsulates the list
 * items along with the the current size of the list.
 */
// maximum number of elements our list data type can hold
const int MAX_LIST_SIZE = 100;
struct ListType
{
  int size;                // number of items currently in list.
  int item[MAX_LIST_SIZE]; // the actual list items;
};

/** ListType constructor
 * Initialize or construct a list of the indicated size.
 * We initialize the list values all to the given initial
 * value.
 *
 * @param list A ListType abstract data type that we should
 *   should initialize.  This is passed by reference so we can
 *   modify the list to return to the caller.
 * @param size The number of elements to initialize
 * @param value The value to initialize the list to.  The default
 *   is to initialize to 0 if not specified.
 *
 * @returns void but implicitly the list is modified.
 */
void initializeList(ListType& list, int size, int value = 0)
{
  for (int i = 0; i < size; i++)
  {
    list.item[i] = value;
  }
  list.size = size;
}

/** display ListType
 * Display the contents of a ListType on cout.
 *
 * @param list A ListType abstract data type that we should
 *   display.  We declare the list to be const because this
 *   function only accesses the list, it does not change
 *   the list.
 *
 * @returns void
 */
void displayList(const ListType& list)
{
  cout << "List size: " << list.size << " items: [ ";
  for (int i = 0; i < list.size; i++)
  {
    cout << list.item[i] << ", ";
  }
  cout << "]" << endl;
}

/** append item to ListType
 * Append an item to the end of our ListType.  This causes the list
 * to grow in size.
 *
 * @param list A ListType abstract data type to be appended.  The list
 *   is passed by reference to that we can modify the list.
 * @param value An integer value to be appended to end of the list.
 */
void appendList(ListType& list, int value)
{
  // minimal error checking we aren't going beyond storage capacity
  if (list.size >= MAX_LIST_SIZE)
  {
    cout << "<appendList()> Error: attempt to append to full list" << endl;
    return;
  }

  // append the value
  list.item[list.size] = value;

  // making sure we keep the list ADT up to date
  list.size++;
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
  // Declaring struct and accessing them ----------------------------------
  // struct are "Records", non-homogeneous collections of data.
  // struct are our second example of a user defined data type, you are adding a new
  // type to language, of which you can create variables of that type.
  HouseType myHouse;
  myHouse.style = COUNTRY;
  myHouse.address = "123 Main Street, Commerce, TX";
  myHouse.numOfBedrooms = 3;
  myHouse.numOfBathrooms = 2;
  myHouse.numOfCarsGarage = 2;
  myHouse.yearBuilt = 1998;
  myHouse.finishedSquareFootage = 1500;
  myHouse.price = 125000.00;
  myHouse.tax = 2000.00;

  // we can access (read out) members using same .memberName synatx.  As usual, we can
  // read out for I/O output, for a calculation/expression, etc.
  cout << "I live at: " << myHouse.address << endl;
  cout << "I pay $" << myHouse.tax << " annual TX property tax" << endl;

  // Assignment, comparison and I/O ---------------------------------------
  // Assignment is defined for struct (unlike for arrays)
  HouseType myBeachHouse;
  myBeachHouse = myHouse;
  cout << "My beach house is at: " << myBeachHouse.address << endl;

  // assignment is by value, e.g. a copy is made.  So myOtherHouse is a completely
  // new house
  myBeachHouse.address = "123 Gulf Blvd.  South Padre Island, TX";
  cout << "My first house is at: " << myHouse.address << endl;
  cout << "My other house is at: " << myBeachHouse.address << endl;

  // Though struct do support assignment, you cannot output or access the whole struct
  // in one operation for anything other than assignment.  For example, cout doesn't
  // know how to output a struct
  // cout << "what happens if I send my whole house to output? " << myHouse << endl;

  // likewise can't compare whole structs
  // if (myHouse == myBeachHouse)
  if (myHouse.address == myBeachHouse.address)
  {
    cout << "They are the same house" << endl;
  }
  else
  {
    cout << "They are different houses" << endl;
  }

  // struct and functions ------------------------------------------------
  // struct can be passed to functions.  Unlike arrays, they act more like simple variables.
  // e.g. by default they are passed by value (e.g. a copy is made).  So a function
  // that we pass a struct into, if we modify the struct parameter in the function, this
  // doesn't effect the caller.
  // so for example, first normal pass by value (copy)
  setHouseStyle(myHouse, TUDOR);
  cout << "After calling <setHouseStyle()>, my style is now: " << styleToString(myHouse.style) << endl;

  // but we can pass struct by reference if we want
  setHousePrice(myHouse, 200000.00); // price was 125000, but we did some remodeling
  cout << "After calling <setHousePrice()>, my price is now: $" << myHouse.price << endl;

  // struct and arrays ----------------------------------------------------
  // It is very useful to be able to have arrays of a struct.  E.g. if we are
  // building a real estate application, we need a database of many houses.
  const int MAX_HOUSES = 100;
  HouseType houseDatabase[MAX_HOUSES];
  for (int i = 0; i < MAX_HOUSES; i++)
  {
    houseDatabase[i].style = RANCH;
    houseDatabase[i].address = "House #" + to_string(i);
    houseDatabase[i].price = 100000.00;
  }

  // at random, show house was initialized from previous loop
  int houseId = 75;
  cout << "The 75th house: " << styleToString(houseDatabase[houseId].style) << " " << houseDatabase[houseId].address << " $"
       << houseDatabase[houseId].price << endl;

  // it is possible, and in fact very useful, to have an array of items be
  // a member of a struct.  So for example, instead of writing functions where
  // we pass in the size of a list, along with the list elements, we can create
  // a new abstract List data type, as shown in the textbook
  ListType myList;
  initializeList(myList, 10, 25);
  myList.item[3] = 32;
  myList.item[5] = 18;
  cout << "After initializing list, the list looks like: " << endl;
  displayList(myList);

  appendList(myList, 42);
  appendList(myList, -10);
  appendList(myList, 99);
  cout << "After appending 3 values, the list looks like: " << endl;
  displayList(myList);

  // return 0 to indicate successful completion
  return 0;
}
