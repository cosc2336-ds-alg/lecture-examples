/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   January 18, 2019
 * @assg   C++ Searching
 *
 * @description Sequential and Binary Search.
 */
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/** sequential search
 * Perform a sequential (linear) search through an array
 * of strings, looking for a particular string.  This
 * function returns the index of the locaiton of the item, if
 * found, or a NOT_FOUND flag if search is unsuccessful.
 *
 * @param list[] An array of strings to search
 * @param listLength The length of the list we have been passed.
 * @param searchItem The string to search for.
 *
 * @return int Return the integer index of item location for successful
 *   search, or NOT_FOUND if unsuccessful.
 */
const int NOT_FOUND = -1;
int sequentialSearch(const string list[], int listLength, string searchItem)
{
  int location; // location/index of item if found

  // search list sequential for the searchItem starting at
  // location 0
  location = 0;
  while (location < listLength)
  {
    if (list[location] == searchItem)
    {
      return location;
    }
    location++;

    // cout << "<sequentialSearch> iteration: " << location << endl;
  }

  // if we get through the loop without finding the item, then
  // search was unsuccessful.
  return NOT_FOUND;
}

/** binary search
 * Given a list of sorted names (string) perform a binary search for the
 * indicated searchItem.
 *
 * @param list[] A list of names of type string to search
 * @param listLength The number of names in the list.
 * @param searchItem The name (a string) to search for.
 *
 * @return int Returns the index where item was found, or returns
 *   NOT_FOUND to indicate unsuccessful search.
 */
int binarySearch(const string list[], int listLength, string searchItem)
{
  // start with the whole list, e.g. first = index 0 and last = last index in list
  int first = 0;
  int last = listLength - 1;
  int mid;

  bool found = false;

  int iteration = 0;

  while ((first <= last) && (!found))
  {
    iteration++;

    // determine item index in middle of current list
    mid = (first + last) / 2; // integer division, removes fractional part

    cout << "<BinarySearch> loop iteration: " << iteration << " first = " << first << " last = " << last << " mid = " << mid << endl;

    // test if we have succeeded in finding our item
    if (list[mid] == searchItem)
    {
      found = true;
    }
    // if we didn't find it, if the item at mid is bigger than searchItem, this
    // means item is lower (to the left) of mid
    else if (list[mid] > searchItem)
    {
      last = mid - 1;
    }
    // otherwise this means item at mid is smaller than search item, so search item
    // must be higher (to the right) of mid
    else
    {
      first = mid + 1;
    }

    // keep searching, but now on only 1/2 of original list, we eliminate 1/2
    // of list each time through the loop
  }

  cout << "<BinarySearch> finished, found = " << found << " mid = " << mid << endl;

  if (found)
  {
    return mid;
  }
  else
  {
    return NOT_FOUND;
  }
}

/** bubble sort
 * Perform a bubble sort on the list of strings.  We are given the list
 * and its length as input.  This function sorts the strings in place using
 * increasing alphabetical order.
 *
 * @param list[] An array of strings to sort
 * @param length The number of strings in the list
 *
 * @return void Nothing returned explicitly, but since list[] is passed
 *   implicitly by reference, the strings are sorted and returned in the
 *   original list parameter given to this funciton.
 */
void bubbleSort(string list[], int length)
{
  string temp; // temporary space to perform a swap of items

  for (int iteration = 1; iteration < length; iteration++)
  {
    for (int index = 0; index < length - iteration; index++)
    {
      // if out of order (alphabetical)
      if (list[index] > list[index + 1])
      {
        // swap the two items
        temp = list[index];
        list[index] = list[index + 1];
        list[index + 1] = temp;
      }
    }
  }
}

/** list to string
 * Convert a list of strings items to a string.  Useful for output/debugging.
 *
 * @param list[] A list of string items;
 * @param length The number of string items in the list.
 *
 * @return string Returns a string representing the contents of the
 *   list.
 */
string listToString(string list[], int length)
{
  ostringstream out;

  out << "List Length: " << length << " [";
  for (int index = 0; index < length; index++)
  {
    out << list[index] << ", ";
  }
  out << "]";

  return out.str();
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
  // test sequential search
  int listLength = 20;
  string names[] = {"Liam", "Emma", "Noah", "Olivia", "William", "Ava", "James", "Isabella", "Logan", "Sophia", "Benjamin", "Mia", "Mason",
    "Charlotte", "Elijah", "Amelia", "Oliver", "Evelyn", "Jacob", "Abigail"};

  string searchItem = "Logan";
  int location = sequentialSearch(names, listLength, searchItem);
  cout << "Search for " << searchItem << ": " << location << endl;

  searchItem = "Liam";
  location = sequentialSearch(names, listLength, searchItem);
  cout << "Search for " << searchItem << ": " << location << endl;

  searchItem = "Abigail";
  location = sequentialSearch(names, listLength, searchItem);
  cout << "Search for " << searchItem << ": " << location << endl;

  searchItem = "Lucas";
  location = sequentialSearch(names, listLength, searchItem);
  cout << "Search for " << searchItem << ": " << location << endl;
  if (location == NOT_FOUND)
  {
    cout << "   search item not found" << endl;
  }

  // need to sort the values before we can do binary search
  bubbleSort(names, listLength);
  cout << endl;
  cout << "Sorted list: " << listToString(names, listLength) << endl;

  // test binary search
  cout << endl;

  searchItem = "Logan";
  location = binarySearch(names, listLength, searchItem);
  cout << "Search for " << searchItem << ": " << location << endl;

  searchItem = "William";
  location = binarySearch(names, listLength, searchItem);
  cout << "Search for " << searchItem << ": " << location << endl;

  searchItem = "Abigail";
  location = binarySearch(names, listLength, searchItem);
  cout << "Search for " << searchItem << ": " << location << endl;

  searchItem = "Lucas";
  location = binarySearch(names, listLength, searchItem);
  cout << "Search for " << searchItem << ": " << location << endl;
  if (location == NOT_FOUND)
  {
    cout << "   search item not found" << endl;
  }

  return 0;
}
