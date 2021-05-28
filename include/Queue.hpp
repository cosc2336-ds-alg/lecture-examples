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
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#ifndef QUEUE_HPP
#define QUEUE_HPP

//-------------------------------------------------------------------------
/** queue (base class)
 * The basic definition of the Queue Abstract Data Type (ADT)
 * and queue operations.  All declared functions here are
 * virtual, they must be implemented by concrete derived
 * classes.
 */
template<class T>
class Queue
{
public:
  /** clear
   * Method to clear out or empty any items on queue,
   * put queue back to empty state.
   * Postcondition: Queue is empty.
   */
  virtual void clear() = 0;

  /** isEmpty
   * Function to determine whether the queue is empty.  Needed
   * because it is undefined to remove from empty queue.  This
   * function will not change the state of the queue (const).
   *
   * @returns bool true if queue is empty, false otherwise.
   */
  virtual bool isEmpty() const = 0;

  /** enqueue
   * Add a new item onto back of queue.
   *
   * @param newItem The item of template type T to add on back of
   *   the current queue.
   */
  virtual void enqueue(const T& newItem) = 0;

  /** front
   * Return the front item from the queue.  Note in this ADT, peeking
   * at the front item does not remove the front item.  Some ADT combine
   * front() and dequeue() as one operation.  It is undefined to try and
   * peek at the front item of an empty queue.  Derived classes should
   * throw an exception if this is attempted.
   *
   * @returns T Returns the front item from queue.
   */
  virtual T front() const = 0;

  /** dequeue
   * Remove the item from the front of the queue.  It is undefined what
   * it means to try and dequeue from an empty queue.  Derived classes should
   * throw an exception if dequeue() from empty is attempted.
   */
  virtual void dequeue() = 0;

  /** length
   * Return the current length or number of item son the queue.
   *
   * @returns int The current length of this queue.
   */
  virtual int length() const = 0;

  /** tostring
   * Represent queue as a string
   */
  virtual string tostring() const = 0;

  // overload output stream operator for all queues using tostring()
  template<typename U>
  friend ostream& operator<<(ostream& out, const Queue<U>& aQueue);
};

//-------------------------------------------------------------------------
/** Empty queue exception
 * Class for empty queue exceptions
 */
class EmptyQueueException
{
private:
  string message;

public:
  EmptyQueueException()
  {
    message = "Error: operation on empty queue";
  }

  EmptyQueueException(string str)
  {
    message = "Error: " + str + " attempted on emtpy queue";
  }

  string what()
  {
    return message;
  }
};

//-------------------------------------------------------------------------
/** queue (array implementation)
 * Implementation of the queue ADT as a fixed array.  This
 * implementation combines a circular buffer implementation, to make
 * sure that both enqueue() and dequeue() operations are O(1) constant
 * time.  However, it also uses dynamic memory allocation, and
 * demonstrates doubling the size of the allocated space as needed to
 * grow queue if/when the queue becomes full.
 *
 * @var allocSize The amount of memory currently allocated for this queue.
 * @var numitems The current length or number of items on the queue.
 * @var front A pointer to the index of the front item on the queue.
 * @var back A pointer to the back or last item on the queu.
 * @var items The items on the queue.  This is a dynamically allocated array that
 *   can grow if needed when queue exceeds current allocation.
 */
template<class T>
class AQueue : public Queue<T>
{
private:
  int allocSize;  // amount of memory allocated
  int numitems;   // The current length of the queue
  int frontIndex; // index of the front item of the queue
  int backIndex;  // index of the last or rear item of the queue
  T* items;

public:
  AQueue(int initialAlloc = 100); // constructor
  ~AQueue();                      // destructor
  void clear();
  bool isEmpty() const;
  bool isFull() const;
  void enqueue(const T& newItem);
  T front() const;
  void dequeue();
  int length() const;
  string tostring() const;
};

//-------------------------------------------------------------------------
/** Node
 * A basic node contaning an item and a link to the next node in
 * the linked list.
 */
template<class T>
struct Node
{
  T item;
  Node<T>* link;
};

/** queue (linked list implementation)
 * Implementation of the queue ADT as a dynamic linked list.  This implementation
 * uses link nodes and grows (and shrinks) the nodes as items enqueued and dequeued
 * onto queue.
 *
 * @var queueFront a pointer to the node holding the front item of the queue.
 * @var queueBack a pointer to the node holding the back item of the queue.
 * @var numitems The length or number of items currently on the queue.
 */
template<class T>
class LQueue : public Queue<T>
{
protected:
  Node<T>* queueFront;
  Node<T>* queueBack;
  int numitems; // the queue length

public:
  LQueue();  // default constructor
  ~LQueue(); // destructor
  void clear();
  bool isEmpty() const;
  void enqueue(const T& newItem);
  T front() const;
  void dequeue();
  int length() const;
  string tostring() const;
};

#endif // QUEUE_HPP
