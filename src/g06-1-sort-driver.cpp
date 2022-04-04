/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  CSci 520, Spring 2022
 * @ide    VSCode Server
 * @date   January 24, 2022
 * @assg   List Insertion Sort
 *
 * @description Sedgwick text, program 6.1
 *   Example of array sort with driver program.  The sort is
 *   actually a version of an insertion sort.
 */
#include <cstdlib>
#include <iostream>
#include <sstream>
using namespace std;

/** @brief items to string
 *
 * Given an array of items, create and return a string of the
 * items in the array, used for display purposes
 *
 * @param items And array of some generic collection of Items.
 *   We assume that the items can be streamed to an output stream.
 *
 * @returns string Returns a representation of the array of items as
 *   a string.
 */
template<class Item>
string itemsToString(int numItems, Item items[])
{
  // output string stream to hold result
  ostringstream out;
  out << "[ ";

  // stream all of the item values into the string
  for (int idx = 0; idx < numItems; idx++)
  {
    out << items[idx];
    if (idx != numItems - 1)
    {
      out << ", ";
    }
  }
  out << " ]";

  // convert to and return a regular string as result
  return out.str();
}

/** @brief exchange items
 *
 * Given references to two separate items, cause the values of the two
 * items to be exchanged (or swapped).
 *
 * @param itemA A reference to one of two items to be exchanged.
 * @param itemB A reference to the second of the two items to be exchanged.
 */
template<class Item>
void exchange(Item& itemA, Item& itemB)
{
  // perform the usual 3 actions to swap items A and B
  Item temp = itemA;
  itemA = itemB;
  itemB = temp;
}

/** @brief compare and exchange
 *
 * Compare the items.  If the items are out of order (B is smaller than
 * A), then exchange the items, to ensure that A is always smaller than B
 * after calling this function.  This method assumes that boolean less
 * than < comparision is defined for the Item type.
 *
 * @param itemA A refernce to one of two items to be compared and put into
 *   ascending order.
 * @param itemB A reference to the other item to be compared and put into
 *   ascending order.
 */
template<class Item>
void compareAndExchange(Item& itemA, Item& itemB)
{
  // test if items are out of order
  if (itemB < itemA)
  {
    // if items are out of order, exchange them to put them in correct
    // ascending order
    exchange(itemA, itemB);
  }
}

/** @brief insertion sort (simple version program 6.1)
 *
 * A simple version of an insertion sort.  We start by assuming the list
 * is of size 1 with first item sorted, then insert unsorted items into
 * the sorted portion of the list.
 *
 * @param items An array of items to be sorted.
 * @param left The left index of the sort to perform.  Usually 0 if we want
 *   to sort the whole array of items.
 * @param right The right index of the sort to perform.  Usually N-1 if we
 *   want to sort the whole array of items.
 */
template<class Item>
void insertionSortNonAdaptive(Item items[], int left, int right)
{
  // outer loop, insert each item from left+1 to right into sorted portion of list.
  for (int i = left + 1; i <= right; i++)
  {
    // inner loop, bubble down the item at current outer index i to correct
    // position, effectively inerting item i into correct sorted portion of list.
    for (int j = i; j > left; j--)
    {
      compareAndExchange(items[j - 1], items[j]);
    }

    // display result after end of each outer loop insertion of 1 item
    // cout << "after inserting item: " << i << endl;
    // cout << itemsToString(right - left + 1, items) << endl;
  }
}

/** @brief selection sort ( program 6.2)
 *
 * Example of selection sort.  Selection sort works by searching for the
 * next smallest item in unsorted portion of the items.  Once smallest item
 * is found, it is exchanged to put it into its correct position in the sorted
 * items.
 *
 * @param items An array of items to be sorted.
 * @param left The left index of the sort to perform.  Usually 0 if we want
 *   to sort the whole array of items.
 * @param right The right index of the sort to perform.  Usually N-1 if we
 *   want to sort the whole array of items.
 */
template<class Item>
void selectionSort(Item items[], int left, int right)
{
  // outer loop, search unfinished/unsorted part of list to
  // find smallest item
  for (int i = left; i < right; i++)
  {
    // inner loop, find minimum item in unsorted part
    int minIndex = i;
    for (int j = i + 1; j <= right; j++)
    {
      if (items[j] < items[minIndex])
      {
        minIndex = j;
      }
    }

    // after the search, minIndex is index of smallest item in unsorted
    // portion of the list, exchange this item with the current index i
    // pointing to left side of unsorted part of list
    exchange(items[i], items[minIndex]);

    // display result after end of each outer loop insertion of 1 item
    // cout << "after searching item: " << i << endl;
    // cout << itemsToString(right - left + 1, items) << endl;
  }
}

/** @brief insertion sort (program 6.3)
 *
 * Insertion sort (program 6.3).  More full/complete implementation of
 * insertion sort than first program 6.1.  Works similar to how most people
 * intuitively sort hand of cards, where you consider 1 card at a time and
 * insert it into correct position in sorted portion of your hand.
 *
 * This implementation first puts smallest element in the array into the
 * first position, so that element can serve as sentinel.  It only does
 * a single assignment to shift values, rather than a swap, in the inner loop.
 * And the inner loop terminates when element being inserted is in position.
 * These improvement make this sort adaptive, it will adapt amount of comparisions
 * and assignments done based on ordering of items given initially, e.g. less
 * work done if array partially or fully orderd to begin with.
 *
 * @param items An array of items to be sorted.
 * @param left The left index of the sort to perform.  Usually 0 if we want
 *   to sort the whole array of items.
 * @param right The right index of the sort to perform.  Usually N-1 if we
 *   want to sort the whole array of items.
 */
template<class Item>
void insertionSort(Item items[], int left, int right)
{
  // an initial pass to bubble smallest item down to left most position
  for (int i = right; i > left; i--)
  {
    compareAndExchange(items[i - 1], items[i]);
  }

  // display array after initial bubble of smallest item down to left index
  // cout << "after bubbling smallest item: " << endl;
  // cout << itemsToString(right - left + 1, items) << endl;

  // at this point, smallest item is in the left index
  // we consider items left and left+1 sorted.  Now start looking at
  // left+2 and inserting item into sorted list
  // outer loop over unsorted part of list from left+2 to right item
  for (int i = left + 2; i <= right; i++)
  {
    // inner loop, shift items up 1 until we find location to insert item i
    int j = i;
    Item itemToInsert = items[i];

    // if item in array is bigger then the item we want to insert, shift it
    // up 1 spot
    while (itemToInsert < items[j - 1])
    {
      items[j] = items[j - 1];
      j--;
    }

    // after the while loop, all items above index j have been shifted up, leaving
    // a hole at index j to insert our item into
    items[j] = itemToInsert;

    // display result after end of each outer loop insertion of 1 item
    // cout << "after inserting item: " << i << endl;
    // cout << itemsToString(right - left + 1, items) << endl;
  }
}

/** @brief bubble sort (program 6.4)
 *
 * Bubble Sort (program 6.4).  Each outer pass bubbles the minimum item in
 * the unsorted portion to its correct position.
 *
 * This version, as shown in the book, is nonadaptive.  We can make it
 * adaptive by keeping track of an inner loop where no exchanges are made,
 * and stopping when that happens.
 *
 * @param items An array of items to be sorted.
 * @param left The left index of the sort to perform.  Usually 0 if we want
 *   to sort the whole array of items.
 * @param right The right index of the sort to perform.  Usually N-1 if we
 *   want to sort the whole array of items.
 */
template<class Item>
void bubbleSort(Item items[], int left, int right)
{
  // outer loop, consider all items unsorted, and perform N passes, where
  // ecah pass of outer loop is guaranteed to bubble the next smallest item
  // down to its correct position
  for (int i = left; i < right; i++)
  {
    // inner loop, bubble down in this implementation from right to
    // current left hand side of unsorted part of the list
    for (int j = right; j > i; j--)
    {
      compareAndExchange(items[j - 1], items[j]);
    }

    // display result after end of each outer loop insertion of 1 item
    // cout << "after outer buble pass: " << i << endl;
    // cout << itemsToString(right - left + 1, items) << endl;
  }
}

/** main
 *
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
  // generate an array or random values.  values range from 0 to 1000
  const int N = 10;
  int items[N];

  for (int idx = 0; idx < N; idx++)
  {
    items[idx] = 1000 * (1.0 * rand() / RAND_MAX);
  }

  cout << "Before sorting the items:" << endl;
  cout << itemsToString(N, items) << endl << endl;

  cout << "Sorting the items..." << endl << endl;
  insertionSortNonAdaptive(items, 0, N - 1);
  // selectionSort(items, 0, N - 1);
  // insertionSort(items, 0, N - 1);
  // bubbleSort(items, 0, N - 1);

  cout << "After sorting the items:" << endl;
  cout << itemsToString(N, items) << endl << endl;

  // return 0 to indicate successfull completion of program
  return 0;
}
