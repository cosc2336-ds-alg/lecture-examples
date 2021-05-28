/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   January 23, 2019
 * @assg   C++ Sorting
 *
 * @description Sorting algorithms and algorithm performance.
 */
#include <chrono> // measure elapsed time of functions using high resolution clock
#include <cmath>
#include <fstream> // file streams to open and read from a file
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/** bubble sort
 * Perform a bubble sort on the list of strings.  We are given the list
 * and its length as input.  This function sorts the strings in place using
 * increasing alphabetical order.
 *
 * Bubble sort is conceptually the simplest sorting algorithm.  We repeatedly
 * compare adjacent items, and if they are out of order we swap them.  On the
 * first pass, the largest item is guaranteed to "bubble" up to the last index
 * of the array.  And on the next pass, the next largest will bubble up to its
 * correct location.  Performing length bubbling passes like this guarantees
 * the resulting list is sorted.
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

  // variables used for logging
  int numIterations = 0;
  int numKeyComparisons = 0;
  int numItemAssignments = 0;

  for (int iteration = 1; iteration < length; iteration++)
  {
    for (int index = 0; index < length - iteration; index++)
    {
      numIterations++; // we are doing another iteration

      // if adjacent items are out of order (alphabetical)
      numKeyComparisons++; // we will do a comparison in next step
      if (list[index] > list[index + 1])
      {
        // swap the two items
        temp = list[index];
        list[index] = list[index + 1];
        list[index + 1] = temp;
        numItemAssignments += 3; // just did 3 assignments
      }
    }
  }

  // log bubbleSort performance before returning
  cout << "<bubbleSort> numIterations: " << numIterations << " numKeyComparisons: " << numKeyComparisons
       << " numItemAssignments: " << numItemAssignments << endl;
}

/** insertion sort
 * Perform an insertion sort on the list of strings.  We are given the list
 * and its length as input.  This function sorts the strings in place using
 * increasing alphabetical order.
 *
 * Conceptually insertion works by keeping track of a sorted and unsorted
 * portion of the list of items.  Initially we consider the item at index
 * 0 to be a list of size 1 that is sorted by definition.  Then we look
 * at the next item (at index 1) and if it is out of order, we insert it
 * into the sorted list by shifting items to make room to insert the
 * item where it needs to go.
 *
 * @param list[] An array of strings to sort
 * @param length The number of strings in the list
 *
 * @return void Nothing returned explicitly, but since list[] is passed
 *   implicitly by reference, the strings are sorted and returned in the
 *   original list parameter given to this funciton.
 */
void insertionSort(string list[], int length)
{
  int firstOutOfOrder;
  int location;
  string temp; // for moving item to correct location

  // variables used for logging
  int numIterations = 0;
  int numKeyComparisons = 0;
  int numItemAssignments = 0;

  // initially only item at index 0 (list of size 1) in sorted list
  // so in the outer loop, search for item that should go in front
  // of that item
  for (firstOutOfOrder = 1; firstOutOfOrder < length; firstOutOfOrder++)
  {
    // find next item in sorted list that is out of order
    numKeyComparisons++; // about to do a comparison
    if (list[firstOutOfOrder] < list[firstOutOfOrder - 1])
    {
      // save the item to a temporary location so we can move it
      temp = list[firstOutOfOrder];
      location = firstOutOfOrder;

      numItemAssignments += 1; // depends on definition of item assignment

      // this loop shifts all of the items up one until we arrive
      // at the correct place to insert the item we found that is out
      // of order
      do
      {
        numIterations++; // we are doing another iteration

        list[location] = list[location - 1];
        numItemAssignments += 1; // shifting causes 1 item assignemnt each time

        location--;

        // we are actually doing a key comparison each time in the while
        // loop to determine if we are done shifting
        numKeyComparisons++;
      } while (location > 0 && list[location - 1] > temp);

      // actually move the item to its correct location after all items
      // bigger have been shifted up to make room
      list[location] = temp;
      numItemAssignments += 1; // the final move is another item assignment
    }
    else
    {
      // if we completly skip over having to shift items, we still did 1
      // outer loop iteration
      numIterations++;
    }
  }

  // log insertionSort performance before returning
  cout << "<insertionSort> numIterations: " << numIterations << " numKeyComparisons: " << numKeyComparisons
       << " numItemAssignments: " << numItemAssignments << endl;
}

/** selection sort
 * Perform a selection sort on the list of strings.  We are given the list
 * and its length as input.  This function sorts the strings in place using
 * increasing alphabetical order.
 *
 * Selection sort works by keeping a sorted and unsorted portion of the list
 * Conceptually, we search for the smallest item in the unsorted portion
 * of the list, and move it to the top of the sorted list.  So the first time
 * we search the whole list and find the smallest item, and it is selcted to
 * move to index 0.  Then we search the remaining unsorted items in index 1
 * to length, find the next smallest item, and it is selected to move to
 * index 1, etc.
 *
 * @param list[] An array of strings to sort
 * @param length The number of strings in the list
 *
 * @return void Nothing returned explicitly, but since list[] is passed
 *   implicitly by reference, the strings are sorted and returned in the
 *   original list parameter given to this funciton.
 */
void selectionSort(string list[], int length)
{
  int index;
  int smallestIndex; // used to search for smallest item in unsorted part of list
  int location;
  string temp; // used to move/swap the item selected to its correct position

  // variables used for logging
  int numIterations = 0;
  int numKeyComparisons = 0;
  int numItemAssignments = 0;

  // search for smallest item in the unsorted portion of the list.
  // initially the list is completely unsorted, so we must search the
  // whole list for the smallest item
  for (index = 0; index < length - 1; index++)
  {
    // step a: find the location of the smallest element
    smallestIndex = index; // smallest we have seen so far is at start of unsorted part

    for (location = index + 1; location < length; location++)
    {
      numIterations++; // we just did another iteration

      // anytime we see something even smaller, remember it instead
      numKeyComparisons++; // we are comparing keys
      if (list[location] < list[smallestIndex])
      {
        smallestIndex = location;
      }
    }

    // step b: move the smallest element to the beginning of the unsorted list
    // we do this by swapping the element that is there with the smallest one we found
    temp = list[smallestIndex];
    list[smallestIndex] = list[index];
    list[index] = temp;

    numItemAssignments += 3; // 3 item assignments doe
  }

  // log selection Sort performance before returning
  cout << "<selectionSort> numIterations: " << numIterations << " numKeyComparisons: " << numKeyComparisons
       << " numItemAssignments: " << numItemAssignments << endl;
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

/** load strings from file
 * Load a list of strings from a file.  The file format is
 * one string per line.  The list of strings is passed in by
 * reference, so implicitly the strings we load from the file and
 * assign to the list willbe returned to the caller.  This function
 * reads in the first listLength strings from the file, or stops
 * if we reach the end of the file.  The list length is passed
 * in by reference, so that if we read in less than the requested
 * number of strings, the new length is returned in this parameter.
 *
 * @param list[] An empty string array, we will fill with strings read from
 *   a file.
 * @param length The number of items maximum to read from file.  Parameter
 *   is passed by reference, so if less items read the new length is
 *   returned as this parameter.
 * @param fileName The name of the file to open and read from.
 */
void loadListFromFile(string list[], int& length, string fileName)
{
  ifstream filein(fileName); // file input stream

  // error check, make sure we really opened the file correctly
  if (!filein)
  {
    cerr << "<loadListFromFile> Error: file not found '" << fileName << "'" << endl;
    exit(0);
  }

  // keep track of the number of items read
  int numItem = 0;
  string item;

  // read items line by line from file into our list of strings
  while (!filein.eof() && (numItem < length))
  {
    filein >> list[numItem];
    numItem++;
  }

  // set the length to what we found
  length = numItem;
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
  const int MAX_NAMES = 10000;
  string names[MAX_NAMES];
  int length = MAX_NAMES;

  // test bubble sort
  loadListFromFile(names, length, "list-of-names.txt");
  // loadListFromFile(names, length, "c:\\users\dash\downloads\list-of-names.txt"); // windows absolute path name
  cout << "<loadListFromFile> Got names: " << listToString(names, 10) << endl;
  cout << "<loadListFromFile> loaded " << length << " names from file." << endl;

  auto start = chrono::high_resolution_clock::now();
  bubbleSort(names, length);
  auto finish = chrono::high_resolution_clock::now();
  chrono::duration<double> elapsed = finish - start;
  cout << "   Expected key comparisons: " << (length * (length - 1)) / 2 << endl;
  cout << "   Average item assignments : " << 3 * (length * (length - 1)) / 4 << endl;
  cout << "   Bubble Sort elapsed time: " << elapsed.count() << " sec" << endl;

  // test insertion sort
  // reload the list, so it is unsorted again before sorting and in exactly the
  // same order for fair tests
  loadListFromFile(names, length, "list-of-names.txt");
  cout << endl;
  cout << "<loadListFromFile> Got names: " << listToString(names, 10) << endl;
  cout << "<loadListFromFile> loaded " << length << " names from file." << endl;

  start = chrono::high_resolution_clock::now();
  insertionSort(names, length);
  finish = chrono::high_resolution_clock::now();
  elapsed = finish - start;
  cout << "   Average key comparisons: " << (int)(pow(length, 2) + 3 * length - 4) / 4 << endl;
  cout << "   Average item assignments : " << (length * (length - 1)) / 4 << endl;
  cout << "   Insertion Sort elapsed time: " << elapsed.count() << " sec" << endl;

  // test selection sort
  // reload the list, so it is unsorted again before sorting and in exactly the
  // same order for fair tests
  loadListFromFile(names, length, "list-of-names.txt");
  cout << endl;
  cout << "<loadListFromFile> Got names: " << listToString(names, 10) << endl;
  cout << "<loadListFromFile> loaded " << length << " names from file." << endl;

  start = chrono::high_resolution_clock::now();
  selectionSort(names, length);
  finish = chrono::high_resolution_clock::now();
  elapsed = finish - start;
  cout << "   Expected key comparisons: " << (length * (length - 1)) / 2 << endl;
  cout << "   Expected item assignments : " << 3 * (length - 1) << endl;
  cout << "   Insertion Sort elapsed time: " << elapsed.count() << " sec" << endl;

  return 0;
}
