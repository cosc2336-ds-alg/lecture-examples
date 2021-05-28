/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   March 1, 2019
 * @assg   C++ Queues videos
 *
 * @description A Queue ADT with two concrete impelementation
 *   examples: an array based queue implementaiton (AQueue), and
 *   a linked list based implementation (LQueue).
 */
#include "Queue.hpp"
#include "Customer.hpp"
#include <iostream>

using namespace std;

//-------------------------------------------------------------------------
/** Queue output stream operator
 * Friend function for Queue ADT, overload output stream operator to allow
 * easy output of queue representation to an output stream.
 */
template<typename U>
ostream& operator<<(ostream& out, const Queue<U>& aQueue)
{
  out << aQueue.tostring();
  return out;
}

//-------------------------------------------------------------------------
/** queue (array) constructor
 * Constructor for queue.  Default to enough room for 100 items
 * NOTE: the front pointer points directly to the index of the front item, but
 * the backIndex pointer points to the index-1 of the item where next insertion
 * will happen.
 * NOTE: we treat the items array as a circular buffer, so all increments of
 * indexes must be modulo current allocSize, to wrap backIndex around to beginning.
 *
 * @param initialAlloc Initial space to allocate for queue, defaults to
 *   100.
 */
template<class T>
AQueue<T>::AQueue(int initialAlloc)
{
  allocSize = initialAlloc;
  numitems = 0;
  frontIndex = 0;
  backIndex = allocSize - 1; // back points to (x-1) % allocSize index
  items = new T[allocSize];
}

/** queue (array) destructor
 */
template<class T>
AQueue<T>::~AQueue()
{
  // free up currently allocated memory
  delete[] items;
}

/** queue (array) clear
 * Function to initialize the queue back to an empty state.
 * Postcondition: frontIndex = 0; backIndex = allocSize-1; numitems=0; isEmpty() == true
 */
template<class T>
void AQueue<T>::clear()
{
  frontIndex = 0;
  backIndex = allocSize - 1;
  numitems = 0;
}

/** queue (array) isEmpty
 * Determine whether queue is currently empty or not.
 *
 * @returns returns true if the queue is empty, otherwise
 *   returns false.
 */
template<class T>
bool AQueue<T>::isEmpty() const
{
  return numitems == 0;
}

/** queue (array) isFull
 * Determine whether queue is currently full or not.
 *
 * @returns returns true if the queue is full, otherwise
 *   returns false.
 */
template<class T>
bool AQueue<T>::isFull() const
{
  return numitems == allocSize;
}

/** queue (array) enqueue
 * Add newItem to the back of the queue.
 * Preconditon: The queue exists
 * Postcondition: The queue is changed and newItem is added to the back
 *   of the queue.
 * @param newItem The new item to add to the frontIndex of this queue.
 */
template<class T>
void AQueue<T>::enqueue(const T& newItem)
{
  // if queue is full, grow it
  if (isFull())
  {
    // double the current size
    int newAllocSize = 2 * allocSize;

    // alloc the new space
    T* newItems = new T[newAllocSize];

    // and copy the queue to the new storage space
    // since we are copying anyway, we shift the items from the old
    // frontIndex back to index 0
    int oldIndex = frontIndex;
    for (int index = 0; index < numitems; index++)
    {
      newItems[index] = items[oldIndex];
      oldIndex = (oldIndex + 1) % allocSize;
    }
    frontIndex = 0;
    backIndex = numitems - 1;

    // free up the old space, start using the new space
    delete[] items;
    items = newItems;
    allocSize = newAllocSize;
  }

  // add the item, and increment our top
  backIndex = (backIndex + 1) % allocSize;
  numitems++;
  items[backIndex] = newItem;
}

/** queue (array) front
 * Peek at and return the front element of the queue.
 * Preconditon: The queue exists and is not empty
 * Postcondition: If the queue is empty, we throw QueueEmpty
 *   exception; otherwise, the front element of the queue is
 *   returned
 * @returns T The item of type T currently on the front of this
 *   queue.
 */
template<class T>
T AQueue<T>::front() const
{
  // assert(topIndex != 0);
  if (isEmpty())
  {
    throw EmptyQueueException("AQueue<T>::front()");
  }
  else
  {
    return items[frontIndex];
  }
}

/** queue (array) dequeue
 * Remove the front element from the queue.  Some ADT combine dequeue
 * and front.  We have two separate operations in this ADT.
 * Preconditon: The queue exists and is not empty.
 * Postcondition: If the queue is empty, we throw QueueEmpty
 *   exception; otherwise the front element of the queue is removed
 *   from the queue.
 */
template<class T>
void AQueue<T>::dequeue()
{
  // assert(topIndex != 0);
  if (isEmpty())
  {
    throw EmptyQueueException("Aqueue<T>::dequeue()");
  }
  else
  {
    numitems--;
    frontIndex = (frontIndex + 1) % allocSize;
  }
}

/** queue (array) length
 * Getter method to access the current queue length.
 *
 * @returns length Returns the current queue length.
 */
template<class T>
int AQueue<T>::length() const
{
  return numitems;
}

/** queue (array) tostring
 * Represent this queue as a string.
 *
 * @returns string Returns the contents of queue as a string.
 */
template<class T>
string AQueue<T>::tostring() const
{
  ostringstream out;

  out << "Front: ";
  int index = frontIndex;
  while (index != (backIndex + 1) % allocSize)
  {
    out << items[index] << " ";
    index++;
  }
  out << ":Back" << endl;

  return out.str();
}

//-------------------------------------------------------------------------
/** queue (list) constructor
 * Constructor for linked list version of queue.
 * An empty queue is indicated by both front and back
 * pointers pointing to null.
 */
template<class T>
LQueue<T>::LQueue()
{
  queueFront = NULL;
  queueBack = NULL;
  numitems = 0;
}

/** queue (list) destructor
 * Destructor for linked list version of queue.
 */
template<class T>
LQueue<T>::~LQueue()
{
  clear();
}

/** queue (list) clear
 * This will empty out the queue.  This method frees up all of the
 * dynamically allocated memory being used by the queue linked list
 * nodes.
 */
template<class T>
void LQueue<T>::clear()
{
  Node<T>* temp;

  // iterate through Nodes in queue, freeing them up
  // as we visit them
  while (queueFront != NULL)
  {
    temp = queueFront;
    queueFront = queueFront->link;

    // dellocate this Node memory
    delete temp;
  }

  // make sure all private members are cleard correctly
  queueBack = NULL;
  numitems = 0;
}

/** queue (list) isEmpty
 *
 */
template<class T>
bool LQueue<T>::isEmpty() const
{
  return queueFront == NULL;
  // return numitems == 0;
}

/** queue (list) enqueue
 * Add the indicated item onto the back of the queue.
 *
 * @param newItem The new item we will add to the back of
 *   this queue.
 */
template<class T>
void LQueue<T>::enqueue(const T& newItem)
{
  // dynamically allocate space for the new Node to hold
  // this newItem
  Node<T>* newNode = new Node<T>;

  // initialize the node
  newNode->item = newItem;
  newNode->link = NULL;

  // if the queue is empty, then this new node is the
  // front and back node
  if (queueFront == NULL)
  {
    queueFront = newNode;
  }
  // otherwise, it gets added onto the back
  else
  {
    queueBack->link = newNode;
  }

  // the new node added is now the new back of the queue
  queueBack = newNode;
  numitems++;
}

/** queue (list) front
 * Return the front item from the queue.
 *
 * @returns T Returns the item currently at the front of
 *   this queue.
 */
template<class T>
T LQueue<T>::front() const
{
  // assert(queueFront != NULL)
  if (isEmpty())
  {
    throw EmptyQueueException("LQueue<T>::front()");
  }
  else
  {
    return queueFront->item;
  }
}

/** queue (list) dequeue
 * This function actually removes the item at the front of the queue from
 * the queue.  It is undefined what happens if you try and dequeue() from
 * an empty queue.  This method throws and exception if dequeue is attempted
 * from an empty queue.
 */
template<class T>
void LQueue<T>::dequeue()
{
  // assert(queueTop != NULL)
  if (isEmpty())
  {
    throw EmptyQueueException("LQueue<T>::dequeue()");
  }
  else
  {
    // keep track of the current front, so we can deallocate
    Node<T>* temp;
    temp = queueFront;

    // remove the front item from the queue
    // if queue becomes empty, make sure both front and back
    // are NULL
    queueFront = queueFront->link;
    if (queueFront == NULL)
    {
      queueBack = NULL;
    }
    numitems--;

    // deallocate the old top now
    delete temp;
  }
}

/** queue (array) length
 * Accessor method to return the current length of this queue.
 *
 * @returns int The current queue length
 */
template<class T>
int LQueue<T>::length() const
{
  return numitems;
}

/** queue (array) tostring
 * Represent this queue as a string.
 *
 * @returns string Returns the contents of queue as a string.
 */
template<class T>
string LQueue<T>::tostring() const
{
  ostringstream out;
  Node<T>* temp = queueFront;

  out << "Front: " << endl;
  while (temp != NULL)
  {
    out << temp->item << "";
    temp = temp->link;
  }
  out << ":Back" << endl;

  return out.str();
}

/**
 * @brief Cause specific instance compilations
 *
 * This is a bit of a kludge, but we can use normal make dependencies
 * and separate compilation by declaring template class
 * Stack<needed_type> here of any types we are going to be
 * instantianting with the template.
 *
 * https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
 * https://isocpp.org/wiki/faq/templates#separate-template-class-defn-from-decl
 */
template class AQueue<string>;
template class LQueue<double>;
template class LQueue<Customer>;

template ostream& operator<<<string>(ostream&, const Queue<string>&);
template ostream& operator<<<double>(ostream&, const Queue<double>&);
template ostream& operator<<<Customer>(ostream&, const Queue<Customer>&);
