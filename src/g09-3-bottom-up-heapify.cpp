/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  CSci 520, Spring 2022
 * @ide    VSCode Server
 * @date   April 18, 2022
 * @assg   algorithms on heaps
 *
 * @description Sedgwick text, program 9.3 - 9.x
 *   Examples of algorithms on heaps.
 */
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


/** @brief bottom-up heapify
 *
 * Fix up a heap.  Given a (usually newly inserted key) that may
 * not be in heap order, "fix-up" the heap, by exchanging the key with
 * parent.  Keep doing this until we arrive at situation where key is
 * in correct location for the heap order, e.g. it is less than or equal to
 * its parent, and greater than both of its children.
 *
 * @param heapItems An array that is assumed to be currently in "heap order"
 *   with the exception of the item at the keyIndex.  An array is in heap
 *   order if it is a full binary tree where each parent key is greater
 *   or equal to both child keys.
 * @param keyIndex The index of the item we are to start the bottom-up
 *   heap fixing process with.  This item may have been newly inserted or
 *   had its priority changed, thus we need to fix the heap upwards starting
 *   at this key.
 */
template<class Item>
void fixUp(Item heapItems[], int itemIndex)
{
  // iterative implementation, keep exchanging the item at itemIndex with its
  // parent as long as the items key is greater than the parent key.  Stop when
  // we reach the root or when the parent has a greater key
  while (itemIndex > 1 and heapItems[itemIndex / 2] < heapItems[itemIndex])
  {
    // exchange the item with its parent since keys are not in heap order
    exchange(heapItems[itemIndex], heapItems[itemIndex / 2]);

    // update itemIndex to parent index where record was just exchanged to, to keep
    // fixing up the heap if needed
    itemIndex = itemIndex / 2;
  }
}


/** @brief top-down heapify
 *
 * Fix up a heap.  Here we assume a key in hap had priority lowered, so may need
 * to fix the heap from top-down.  We fix heap order in top-down fashion by
 * exchanging the key at position itemIndex with the larger of that nodes
 * children.  This stops when the node is not smaller than either child or the
 * bottom has been reached.
 *
 * @param heapItems An array that is assumed to be currently in "heap order"
 *   with the exception of the item at the keyIndex.  An array is in heap
 *   order if it is a full binary tree where each parent key is greater
 *   or equal to both child keys.
 * @param keyIndex The index of the item we are to start the top-down
 *   heap fixing process with.  This item may have been newly inserted or
 *   had its priority changed, thus we need to fix the heap upwards starting
 *   at this key.
 * @param heapSize To detect if/when we reach the bottom of the full binary
 *   tree heap, need to know the actual current size of the heap array.
 */
template<class Item>
void fixDown(Item heapItems[], int itemIndex, int heapSize)
{
  // iterative implementation, we keep going until the itemIndex is below
  // the current heapSize.  This loop breaks out of itself if it finds a place
  // where the key is not smaller than either child key
  while (2 * itemIndex <= heapSize)
  {
    // exchange with left child
    int childIndex = 2 * itemIndex;

    // except if left child is smaller than right child, exchange with right child instead
    if (childIndex < heapSize and heapItems[childIndex] < heapItems[childIndex + 1])
    {
      childIndex++;
    }

    // check if the item key is bigger, in which case we are done fixing down
    if (heapItems[itemIndex] >= heapItems[childIndex])
    {
      break;
    }

    // otherwise exchange with the larger child and keep fixing down
    exchange(heapItems[itemIndex], heapItems[childIndex]);
    itemIndex = childIndex;
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
  // a heap of character items
  const int N = 32;  // full tree 5 levels deep
  char heapItems1[N] = {' ', 'X', 'S', 'P', 'G', 'R', 'O', 'N', 'A', 'E', 'T', 'A', 'I', 'M'};


  cout << "Before fixing up heap:" << endl;
  cout << itemsToString(N, heapItems1) << endl << endl;
  fixUp(heapItems1, 10);
  cout << "After fixing up heap:" << endl;
  cout << itemsToString(N, heapItems1) << endl << endl;

  char heapItems2[N] = {' ', 'O', 'T', 'X', 'G', 'S', 'P', 'N', 'A', 'E', 'R', 'A', 'I', 'M'};


  cout << "Before fixing down heap:" << endl;
  cout << itemsToString(N, heapItems2) << endl << endl;
  fixDown(heapItems2, 1, 13);
  cout << "After fixing down heap:" << endl;
  cout << itemsToString(N, heapItems2) << endl << endl;

  
  // return 0 to indicate successfull completion of program
  return 0;
}
