/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  CSci 520, Spring 2022
 * @ide    VSCode Server
 * @date   January 24, 2022
 * @assg   Quicksort
 *
 * @description Sedgwick text, program 7.1
 *   Example of array sort with driver program.  
 *   This is the texts implementation of the quicksort recursive sort
 *   and program 7.2 partition function.
 */
#include <algorithm>
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

/** @brief partition (program 7.2)
 *
 * Partition a list.  In this implementation we partition the list based on the
 * right most value of the list items.  All values less than this value should end up
 * below the partition value, and all values greater will be above it in the returned
 * partitioned list.  We return the partition index where the value ended up being placed,
 * which is the correct position for this value to be for the final sorted list.
 *
 * This partition function is not stable because values equal to the partition value
 * being used here will get put after it in the partitioned list, thus they change
 * position relative to their original order in the list.
 *
 * @param items An array of items to be sorted.
 * @param left The left index of the sort to perform.  Usually 0 if we want
 *   to sort the whole array of items.
 * @param right The right index of the sort to perform.  Usually N-1 if we
 *   want to sort the whole array of items.
 */
template<class Item>
int partition(Item items[], int left, int right)
{
  // variable used for the partitioning
  int leftPosition = left - 1;
  int rightPosition = right;
  Item pivotValue = items[right];

  // keep finding values to swap into correct side of the partition
  while (true)
  {
    // find the next value in left that is bigger than the partition value
    while (items[++leftPosition] < pivotValue)
    {
      // nothing to do, the leftPosition should end up pointing to next value on the
      // left side that is on wrong side of partition
    }

    // likewise find next value in right side that is smaller than the partition value
    while (pivotValue < items[--rightPosition])
    {
      // stop searching if we the left and right positions cross
      if (rightPosition == leftPosition)
      {
	break;
      }
    }

    // if left and right positions have crossed, we finished the partition, so stop
    // searching for values to exchange
    if (leftPosition >= rightPosition)
    {
      // at this point the leftPosition will be the index where the pivotValue should be placed
      break;
    }

    // otherwise exchange the position of the two values on the wrong sides we just found and
    // keep searching for more
    exchange(items[leftPosition], items[rightPosition]);
  }

  // After the partitioning loop, the leftPosition should point to the final index where the
  // pivotValue should be placed.  We first exchange the pivotValue we used to its correct
  // location  NOTE: we use the original right index here which was the location of the
  // pivotValue we used for the partition
  exchange(items[leftPosition], items[right]);

  // and finally return the pivot index we found so we can recursivley sort the now
  // partitioned lower and upper partitions
  return leftPosition;
}

/** @brief quicksort (program 7.1)
 *
 * Texts basic implementation of the quicksort.  This is a divide-and-conquer
 * algorithm.  Most of the work is actually done by the partition function.
 * This method partitions the list into 2 parts based on a pivot values, which is
 * correctly sorted to its kth position.  Then we recursively call quicksort on
 * the unsorted parts below and above the partitioned value.
 *
 * @param items An array of items to be sorted.
 * @param left The left index of the sort to perform.  Usually 0 if we want
 *   to sort the whole array of items.
 * @param right The right index of the sort to perform.  Usually N-1 if we
 *   want to sort the whole array of items.
 */
template<class Item>
void quickSort(Item items[], int left, int right)
{
  // base case, if right is equal to left or smaller, there is one or zero
  // remaining values to sort, so nothing left to be done on a list of size 1
  // or smaller
  if (right <= left)
  {
    return;
  }

  // otherwise partition the list into 2 parts.  The partition function returns
  // the pivot index that was used.
  int pivotIndex = partition(items, left, right);

  // based on the pivot index, the value at this index is now in the correct
  // position.  So sort all of the values below and above this pivot index.
  quickSort(items, left, pivotIndex - 1);
  quickSort(items, pivotIndex + 1, right);
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

  generateRandomInts(N, items);
  cout << "Before sorting the items:" << endl;
  cout << itemsToString(N, items) << endl << endl;
  cout << "Sorting the items using quicksort..." << endl << endl;
  quickSort(items, 0, N - 1);
  cout << "After sorting the items:" << endl;
  cout << itemsToString(N, items) << endl << endl;

  // return 0 to indicate successfull completion of program
  return 0;
}
