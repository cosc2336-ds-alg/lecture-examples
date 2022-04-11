/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  CSci 520, Spring 2022
 * @ide    VSCode Server
 * @date   January 24, 2022
 * @assg   Mergesort
 *
 * @description Sedgwick text, program 8.1 - 8.x
 *   Example of array sort with driver program.  
 *   This is the texts implementation of the mergesort recursive sort
 *   and additional functions to support mergesort.
 */
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
using namespace std;


// Global constants, the maximum number of values N we are creating and
// sorting examples with
const int N = 10;


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

int numberOfExchanges;

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
  numberOfExchanges++;
  Item temp = itemA;
  itemA = itemB;
  itemB = temp;
}

int numberOfComparisons;

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
  numberOfComparisons++;
  if (itemB < itemA)
  {
    // if items are out of order, exchange them to put them in correct
    // ascending order
    exchange(itemA, itemB);
  }
}


/** @brief generate random int items
 *
 * Generate an array of size N of random integers.  We generate
 * integers in the range from 1 to 1000 in this example.
 *
 * We set the random seed to a constant value so that every time
 * we call this function, it generates the same random sequence of
 * inteteger values.
 *
 * @param numItems The size of the array to generate random values
 *   for.
 * @param items The array of items to randomly gnerate
 */
void generateRandomInts(int numItems, int items[])
{
  // set random seed so we always generate same sequence of random values.
  srand(42);

  // generate the random integers in range from 1 to 1000
  for (int idx = 0; idx < numItems; idx++)
  {
    items[idx] = 1000 * (1.0 * rand() / RAND_MAX);
  }
}

/** @brief merge sorted lists (program 8.1)
 *
 * Given two lists as inputs, and assuming that the lists are sorted before this
 * function is called, merge the lists into a new list such that the new merged
 * list of items is also sorted.
 *
 * We are given inputItems1 and inputItems2 lits with their respective sizes.
 * The resultItems needs to be big enough to hold size1 + size2 resulting
 * items.
 *
 * @param resultItems An array of items that will hold the merged results.
 * @param inputItems1 The first set of sorted items to be merged into the result.
 * @param size1 The number of items in the first sorted set of inputs.
 * @param inputItems2 The second set of sorted items to be merged into the result.
 * @param size2 The number of items in the second sorted set of inputs.
 */
template<class Item>
void mergeSortedLists(Item resultItems[],
		      Item inputItems1[], int size1,
		      Item inputItems2[], int size2)
{
  // declare variables used for iterating through inputs to merge to the result
  int resultSize = size1 + size2;
  int resultPosition = 0;
  int inputPosition1 = 0;
  int inputPosition2 = 0;

  // copy all size1 + size2 values from inputs into the result
  while (resultPosition < resultSize)
  {
    // special case, if out of items 1, just copy items from items2
    if (inputPosition1 == size1)
    {
      resultItems[resultPosition] = inputItems2[inputPosition2++];
      continue;  // continue copying items from 2
    }

    // and other special case, if out of items 2, just copy items from items1
    if (inputPosition2 == size2)
    {
      resultItems[resultPosition] = inputItems1[inputPosition1++];
      continue; // continue copying items from 1
    }

    // otherwise still items in both input 1 and input 2, so copy the item with
    // the smallest value
    if (inputItems1[inputPosition1] < inputItems2[inputPosition2])
    {
      resultItems[resultPosition] = inputItems1[inputPosition1++];
    }
    else
    {
      resultItems[resultPosition] = inputItems1[inputPosition2++];
    }
    
    // update position for next item merge/copy
    resultPosition++;
  }
  
}

/** @brief merge sorted sub lists (program 8.2)
 *
 * Given two lists as inputs, and assuming that the lists are sorted before this
 * function is called, merge the lists into a new list such that the new merged
 * list of items is also sorted.
 *
 * We are given inputItems1 and inputItems2 lits with their respective sizes.
 * The resultItems needs to be big enough to hold size1 + size2 resulting
 * items.
 *
 * @param resultItems An array of items that will hold the merged results.
 * @param inputItems1 The first set of sorted items to be merged into the result.
 * @param size1 The number of items in the first sorted set of inputs.
 * @param inputItems2 The second set of sorted items to be merged into the result.
 * @param size2 The number of items in the second sorted set of inputs.
 */
template<class Item>
void merge(Item items[], int left, int mid, int right)
{
  // left and right positions of merge
  int leftPosition;
  int rightPosition;
  
  // auxillary space, in order to perform in-place merge need to copy
  // to temporary auxillary space, statically allocated means this
  // space is allocated only 1 time in global address space
  static Item auxillary[N];

  // copy items from midpoint down to left side to auxillary.  Notice these end up in
  // same order in auxillary as they were in original
  for (leftPosition = mid + 1; leftPosition > left; leftPosition--)
  {
    auxillary[leftPosition - 1] = items[leftPosition - 1];
  }

  // copy items from midpoint up to right side to auxillary.  But here we
  // reverse the order of these items, so largest ends up at mid point, down to smaller
  for (rightPosition = mid; rightPosition < right; rightPosition++)
  {
    auxillary[right + mid - rightPosition] = items[rightPosition + 1];
  }

  // at this point items have been copied to auxillary, and leftPosition has ended up
  // at left index, and rightPosition has ended up at right index.
  // copy values from auxillary back into items, merging them by order as we go
  for (int itemPosition = left; itemPosition <= right; itemPosition++)
  {
    // if right is the smaller, copy from the right position item
    if (auxillary[rightPosition] < auxillary[leftPosition])
    {
      items[itemPosition] = auxillary[rightPosition--];
    }
    // otherwise left is smaller, so copy the left position item
    else
    {
      items[itemPosition] = auxillary[leftPosition++];
    }
  }
}


/** @brief mergesort (program 8.3)
 *
 * Texts basic implementation of the top-down mergesort algorithm.
 * Another example of a divide-and-conquer.  This method ends up
 * looking relatively simple because most of the complexity
 * happens in the in-place merging of the sorted sub-portions
 * of the list.  We divide list in half, then sort the halves
 * recursively.  When lists are of size 1, the recursion ends, and
 * we end up merging lists of size 1.
 *
 * @param items An array of items to be sorted.
 * @param left The left index of the sort to perform.  Usually 0 if we want
 *   to sort the whole array of items.
 * @param right The right index of the sort to perform.  Usually N-1 if we
 *   want to sort the whole array of items.
 */
template<class Item>
void mergeSort(Item items[], int left, int right)
{
  // base case, if right is equal to or smaller than left, list is of size 1
  // or smaller, so that subportion of list is sorted by definition
  if (right <= left)
  {
    return;
  }

  // otherwise recursive general case. Divide list in half
  int mid = (right + left) / 2;

  // sort the two halves of the list
  mergeSort(items, left, mid);
  mergeSort(items, mid+1, right);

  // now merge the resulting sorted halves in place using merge function
  merge(items, left, mid, right);
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
  int items[N];

  generateRandomInts(N, items);
  cout << "Before sorting the items:" << endl;
  cout << itemsToString(N, items) << endl << endl;
  cout << "Sorting the items using mergeSort..." << endl << endl;
  mergeSort(items, 0, N - 1);
  cout << "After sorting the items:" << endl;
  cout << itemsToString(N, items) << endl << endl;

  // return 0 to indicate successfull completion of program
  return 0;
}
