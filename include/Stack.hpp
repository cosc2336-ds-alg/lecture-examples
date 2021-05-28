/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   January 18, 2019
 * @assg   C++ Stacks  videos
 *
 * @description A Stack ADT with two concrete impelementation
 *   examples: an array based stack implementaiton (AStack), and
 *   a linked list based implementation (LStack).
 */
#include <iostream>
#include <sstream>
#include <string>

#ifndef STACK_HPP
#define STACK_HPP

using namespace std;

//-------------------------------------------------------------------------
/** stack (base class)
 * The basic definition of the Stack Abstract Data Type (ADT)
 * and stack operations.  All declared functions here are
 * virtual, they must be implemented by concrete derived
 * classes.
 */
template<class T>
class Stack
{
public:
  /** clear
   * Method to clear out or empty any items on stack,
   * put stack back to empty state.
   * Postcondition: Stack is empty.
   */
  virtual void clear() = 0;

  /** isEmpty
   * Function to determine whether the stack is empty.  Needed
   * because it is undefined to pop from empty stack.  This
   * function will not change the state of the stack (const).
   *
   * @returns bool true if stack is empty, false otherwise.
   */
  virtual bool isEmpty() const = 0;

  /** push
   * Add a new item onto top of stack.
   *
   * @param newItem The item of template type T to push on top of
   *   the current stack.
   */
  virtual void push(const T& newItem) = 0;

  /** top
   * Return the top item from the stack.  Note in this ADT, peeking
   * at the top item does not remove the top item.  Some ADT combine
   * top() and pop() as one operation.  It is undefined to try and
   * peek at the top item of an empty stack.  Derived classes should
   * throw an exception if this is attempted.
   *
   * @returns T Returns the top item from stack.
   */
  virtual T top() const = 0;

  /** pop
   * Remove the item from the top of the stack.  It is undefined what
   * it means to try and pop from an empty stack.  Derived classes should
   * throw an exception if pop() from empty is attempted.
   */
  virtual void pop() = 0;

  /** tostring
   * Represent stack as a string
   */
  virtual string tostring() const = 0;

  // overload output stream operator for all stacks using tostring()
  template<typename U>
  friend ostream& operator<<(ostream& out, const Stack<U>& aStack);
};

//-------------------------------------------------------------------------
/** Empty stack exception
 * Class for empty stack exceptions
 */
class EmptyStackException
{
private:
  string message;

public:
  EmptyStackException()
  {
    message = "Error: operation on empty stack";
  }

  EmptyStackException(string str)
  {
    message = "Error: " + str + " attempted on emtpy stack";
  }

  string what()
  {
    return message;
  }
};

//-------------------------------------------------------------------------
/** stack (array implementation)
 * Implementation of the stack ADT as a fixed array.  This implementation
 * uses dynamic memory allocation, and demonstrates doubling the size
 * of the allocated space as needed to grow stack.
 *
 * @var allocSize The amount of memory currently allocated for this stack.
 * @var topIndex The index pointing to top item location on stack array.  The stack
 *   grows from 0 up, so the top also indicates the current size of the stack.
 * @var items The items on the stack.  This is a dynamically allocated array that
 *   can grow if needed when stack exceeds current allocation.
 */
template<class T>
class AStack : public Stack<T>
{
private:
  int allocSize; // amount of memory allocated
  int topIndex;  // index to top item on stack, stack
  T* items;

public:
  AStack(int initialAlloc = 100); // constructor
  ~AStack();                      // destructor
  void clear();
  bool isEmpty() const;
  void push(const T& newItem);
  T top() const;
  void pop();
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

/** stack (linked list implementation)
 * Implementation of the stack ADT as a dynamic linked list.  This implementation
 * uses link nodes and grows (and shrinks) the nodes as items popped and pushed
 * onto stack.
 */
template<class T>
class LStack : public Stack<T>
{
public:
  LStack();  // default constructor
  ~LStack(); // destructor
  void clear();
  bool isEmpty() const;
  void push(const T& newItem);
  T top() const;
  void pop();
  string tostring() const;

private:
  Node<T>* stackTop;
};

#endif // STACK_HPP
