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
#include "Stack.hpp"
#include <iostream>
using namespace std;

//-------------------------------------------------------------------------
/** Stack output stream operator
 * Friend function for Stack ADT, overload output stream operator to allow
 * easy output of stack representation to an output stream.
 */
template<typename U>
ostream& operator<<(ostream& out, const Stack<U>& aStack)
{
  out << aStack.tostring();
  return out;
}

//-------------------------------------------------------------------------
/** stack (array) constructor
 * Constructor for stack.  Default to enough room for 100 items
 *
 * @param initialAlloc Initial space to allocate for stack, defaults to
 *   100.
 */
template<class T>
AStack<T>::AStack(int initialAlloc)
{
  allocSize = initialAlloc;
  topIndex = 0;
  items = new T[allocSize];
}

/** stack (array) destructor
 */
template<class T>
AStack<T>::~AStack()
{
  // free up currently allocated memory
  delete[] items;
}

/** stack (array) clear
 * Function to initialize the stack back to an empty state.
 * Postcondition: topIndex = 0; isEmpty() == true
 */
template<class T>
void AStack<T>::clear()
{
  topIndex = 0;
}

/** stack (array) isEmpty
 * Determine whether stack is currently empty or not.
 *
 * @returns returns true if the stack is empty, otherwis
 *   returns false.
 */
template<class T>
bool AStack<T>::isEmpty() const
{
  return topIndex == 0;
}

/** stack (array) push
 * Add newItem to the top of the stack.
 * Preconditon: The stack exists
 * Postcondition: The stack is changed and newItem is added to the top
 *   of the stack.
 * @param newItem The new item to push on top of this stack.
 */
template<class T>
void AStack<T>::push(const T& newItem)
{
  // if stack is full, grow it
  if (topIndex == allocSize)
  {
    // double the current size
    allocSize = 2 * allocSize;

    // alloc the new space
    T* newItems = new T[allocSize];

    // and copy the stack to the new storage space
    for (int index = 0; index < topIndex; index++)
    {
      newItems[index] = items[index];
    }

    // free up the old space, start using the new space
    delete[] items;
    items = newItems;
  }

  // add the item, and increment our top
  items[topIndex] = newItem;
  topIndex++;
}

/** stack (array) top
 * Peek at and return the top element of the stack.
 * Preconditon: The stack exists and is not empty
 * Postcondition: If the stack is empty, we throw StackEmpty
 *   exception; otherwise, the top element of the stack is
 *   returned
 * @param newItem The new item to push on top of this stack.
 */
template<class T>
T AStack<T>::top() const
{
  // assert(topIndex != 0);
  if (topIndex == 0)
  {
    throw EmptyStackException("AStack<T>::top()");
  }
  else
  {
    return items[topIndex - 1];
  }
}

/** stack (array) pop
 * Remove the top element from the stack.  Some ADT combine pop
 * and top.  We have two separate operations in this ADT.
 * Preconditon: The stack exists and is not empty.
 * Postcondition: If the stack is empty, we throw StackEmpty
 *   exception; otherwise the top element of the stack is removed
 *   from the stack.
 */
template<class T>
void AStack<T>::pop()
{
  // assert(topIndex != 0);
  if (topIndex == 0)
  {
    throw EmptyStackException("AStack<T>::pop()");
  }
  else
  {
    topIndex--;
  }
}

/** stack (array) tostring
 * Represent this stack as a string.
 *
 * @returns string Returns the contents of stack as a string.
 */
template<class T>
string AStack<T>::tostring() const
{
  ostringstream out;

  out << "--TopTop--" << endl;
  for (int index = topIndex - 1; index >= 0; index--)
  {
    out << items[index] << endl;
  }
  out << "--Bottom--" << endl;

  return out.str();
}

//-------------------------------------------------------------------------
/** stack (list) constructor
 * Constructor for linked list version of stack.
 */
template<class T>
LStack<T>::LStack()
{
  stackTop = NULL;
}

/** stack (list) destructor
 * Destructor for linked list version of stack.
 */
template<class T>
LStack<T>::~LStack()
{
  clear();
}

/** stack (list) clear
 *
 */
template<class T>
void LStack<T>::clear()
{
  Node<T>* temp;

  // iterate through Nodes in stack, freeing them up
  // as we visit them
  while (stackTop != NULL)
  {
    temp = stackTop;
    stackTop = stackTop->link;

    // dellocate this Node memory
    delete temp;
  }
}

/** stack (list) isEmpty
 *
 */
template<class T>
bool LStack<T>::isEmpty() const
{
  return stackTop == NULL;
}

/** stack (list) push
 *
 */
template<class T>
void LStack<T>::push(const T& newItem)
{
  // dynamically allocate space for the new Node to hold
  // this newItem
  Node<T>* newNode = new Node<T>;

  // initialize the node
  newNode->item = newItem;
  newNode->link = stackTop;

  // now make this new node the new top of stack
  stackTop = newNode;
}

/** stack (list) top
 *
 */
template<class T>
T LStack<T>::top() const
{
  // assert(stackTop != NULL)
  if (stackTop == NULL)
  {
    throw EmptyStackException("LStack<T>::top()");
  }
  else
  {
    return stackTop->item;
  }
}

/** stack (list) pop
 *
 */
template<class T>
void LStack<T>::pop()
{
  // assert(stackTop != NULL)
  if (stackTop == NULL)
  {
    throw EmptyStackException("LStack<T>::pop()");
  }
  else
  {
    // keep track of the current top, so we can deallocate
    Node<T>* temp;
    temp = stackTop;

    // pop off the top
    stackTop = stackTop->link;

    // deallocate the old top now
    delete temp;
  }
}

/** stack (array) tostring
 * Represent this stack as a string.
 *
 * @returns string Returns the contents of stack as a string.
 */
template<class T>
string LStack<T>::tostring() const
{
  ostringstream out;
  Node<T>* temp = stackTop;

  out << "--TopTop--" << endl;
  while (temp != NULL)
  {
    out << temp->item << endl;
    temp = temp->link;
  }
  out << "--Bottom--" << endl;

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
template class AStack<string>;
template class LStack<double>;

template ostream& operator<<<string>(ostream&, const Stack<string>&);
template ostream& operator<<<double>(ostream&, const Stack<double>&);
