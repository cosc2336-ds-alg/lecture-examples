/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   January 18, 2019
 * @assg   C++ Dynamic Memory Video
 *
 * @description Linked List Fundamentals.
 *   Creating, building, inserting and deleting into Linked Lists
 */
#include <iostream>
#include <sstream> // string streams

using namespace std;

/** NodeType container
 * Provide a basic node for implementation of linked lists.  Here we
 * support LinkedLists of int values.  Need a template to support LinkedList
 * of other types of values.
 *
 * @variable info An int value, the item in this node of our linked list.
 * @variable link A pointer to the next NodeType in a linked list, or NULL
 *   if there is no next item after this node in the list.
 */
struct NodeType
{
  int info;
  NodeType* link;
};

/** tostring for a NodeType in a list
 * Create and return a string representation of a linked list of NodeType
 * nodes.
 *
 * @param NodeType* A pointer to an item in a linked list of NodeTypes
 *
 * @returns string Returns a string representation of the integer values
 *   found in the linked list.
 */
string tostring(NodeType* current)
{
  ostringstream out;

  out << "List: [";

  // we display the first one if it exists, so that we don't end
  // the list with a , at the end
  if (current != NULL)
  {
    out << current->info;
    current = current->link;
  }

  // now iterate over items 2 through the end and add them to the
  // string
  while (current != NULL)
  {
    out << ", " << current->info;
    current = current->link;
  }
  out << "]";

  // return the string we built
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
  //-----------------------------------------------------------------------
  // Array based (sequential) vs. dynamically allocated Linked List based
  // See W03-DynamicMemory.cpp for an array based implementation of a ListType

  //-----------------------------------------------------------------------
  // NodeType container, pointers and dynamic memory
  // Remember a pointer is just a memory address.  If you declare a pointer, you
  // have to point it to something to be useful
  NodeType* first; // a memory address, but it doesn't yet point to anything

  // Remember, we can dynamically allocate memory, like a new NodeType

  first = new NodeType;

  // This previous did 2 things, it allocated enough memory for the two member
  // variables of a NodeType (info and link), and it returned the base address of
  // this memory, which we assigned to the first pointer.
  // So what memory address was allocated for this new node?
  cout << "first now points to memory address: " << first << endl;

  // Now that first validly points to something, we can fill it up
  first->info = 17;
  first->link = NULL; // the linked list doesn't yet have a second item

  // we might sometimes create a pointer to a NodeType and allocate what it points
  // to at the same time
  NodeType* last = new NodeType;
  last->info = 45;   // fill in the information for this node
  last->link = NULL; // also not pointing to anything yet

  // We can create some other nodes
  NodeType* node2 = new NodeType;
  node2->info = 92;
  node2->link = NULL;

  NodeType* node3 = new NodeType;
  node3->info = 63;
  node3->link = NULL;

  // These are all 4 separate nodes, allocated somewhere in memory.  They are not
  // yet a linked list.  We can create a link list by out of these nodes.
  // Remember a pointer is just InheritanceCompositiona memory address.  The link member is a pointer.
  // We can copy/set the memory addresses of the link members to create a chain
  // of nodes
  first->link = node2; // first points to node2
  node2->link = node3; // node2 points to node3
  node3->link = last;  // node3 points to last
  // we already did this, but for emphasis, the last item points to NULL, indicating
  // it is the end of the linked list.
  last->link = NULL;

  // the result is the linked list figure 17-4 of our textbook.

  // we can access the items of our list individually.  And we really don't need
  // the node2, node3 or even last pointer variables, we can get them all from the
  // first of the list.

  // The information at the first of the list
  cout << "First info: " << first->info << endl;

  // node2, nod3, and node4 (last) info
  cout << "The second node info: " << first->link->info << endl;
  cout << "The third node info:  " << first->link->link->info << endl;
  cout << "The fourth node (last) info: " << first->link->link->link->info << endl;

  // warning, it is an error and will cause a seg violation to try and follow a
  // null pointer
  // cout << "Warning, don't follow NULL pointers: " << first->link->link->link->link->info << endl;

  // We almost never do the previous to access the second, third, etc item in the list.
  // What if our list has 1 million items, are we really going to put in a million ->
  // to get it?  And in any case, we can't know at compile time what size the list might
  // be, nor which is the position of the item we want to access.  Thus we will usually
  // use a loop to "iterate" through the list in order to access it, display it, search
  // it, etc.  The basic pattern is something like this.
  NodeType* current; // pointer to the current node while we are iterating

  current = first;    // start at the first of the list
  int itemNumber = 1; // just for display purposes

  // iterate till we get to the end of the list
  while (current != NULL)
  {
    cout << "list item[" << itemNumber << "] = " << current->info << endl;

    // important, update current so next time in loop body it advances to
    // next node in list
    itemNumber++;
    current = current->link;
  }

  // this is common enough, we might make a function out of it, for example
  cout << "call function on the first of our list to convert list items to string: " << tostring(first) << endl << endl;

  // be good stewards of memory.  Remember we dynamically allocated the nodes
  // for the example in this section.  We won't be using these again, so free them up

  // careful, we have to proceed from the last up to the first, or instead use a loop.
  delete first->link->link->link; // frees up item 4, the last
  delete first->link->link;       // frees up item 3
  delete first->link;             // frees up item 2
  delete first;                   // frees up item 1, or the first item
  first = last = NULL;

  //-----------------------------------------------------------------------
  // Building a list by adding onto the end.  Normally for a linked list, we keep
  // track of the first and last node of the linked list.  This facilitates easy
  // insertion of an item to the front of the list, and easy appending of an item
  // to the end of a list.  Recall that linked lists main advantage over an array
  // implementation is that it makes this kind of insertion, at end, beginnin or
  // in middle of the list, a relatively indepnsive operation.

  // So when building a new list, we might build it by appending new items to the end,
  // which is relatively easy.  A list starts out empty, and by convention we indicate
  // this by having first and last both initially point ot null;
  first = NULL; // reusing from above
  last = NULL;
  NodeType* newNode; // used to create new nodes in the loop

  // We will perform a loop asking user to input a number or use the flag -1 to
  // indcate they are done, and we will create a linked lit from their input
  int num;
  cout << "Creating list by appending to end..." << endl;
  while (true) // we go forever, or until user enters -1 and we explicitly break out
  {
    // get number from user
    cout << "Enter next number for list (or -1 when done): ";
    cin >> num;

    // test if user said we are done
    if (num == -1)
    {
      break; // and if so break out
    }

    // create node and set up its member fields
    newNode = new NodeType;
    newNode->info = num;
    newNode->link = NULL;

    // if list is empty then the new node is both the first and last
    // item of the list
    if (first == NULL)
    {
      first = newNode;
      last = newNode;
    }
    // list is not empty, so a normal append is to just link the current last
    // to point to the new node, and update last to now point to this new node
    else
    {
      last->link = newNode; // current last now points to this new node we are appending
      last = newNode;       // now newNode is the last node in list
    }
  }

  // after we are done, we can demonstrate loop created list by appending
  // values to end of growing list
  cout << "The list you created by appending: " << tostring(first) << endl << endl;

  // ok we are done with that list, we should free it all up
  current = first; // we will delete all nodes from first to last, being careful not to loose our lis
  while (current != NULL)
  {
    // remember the node we want to delete
    NodeType* nodeToDelete = current;

    // advance current to next node in list for next iteration of loop
    current = current->link;

    // now we can safely delete the node because current now know the next
    // one in the list
    delete nodeToDelete;
  }
  // list is now empty, so lets start again
  first = last = NULL;

  // Ok we created a list by appending values onto the end.  Prepending values to
  // the beginning is pretty similar, if that is how we want to create the list
  cout << "Creating list by inserting/prepending to beginning..." << endl;
  while (true) // we go forever, or until user enters -1 and we explicitly break out
  {
    // get number from user
    cout << "Enter next number for list (or -1 when done): ";
    cin >> num;

    // test if user said we are done
    if (num == -1)
    {
      break; // and if so break out
    }

    // create node and set up its member fields
    newNode = new NodeType;
    newNode->info = num;
    newNode->link = NULL;

    // if list is empty then the new node is both the first and last
    // item of the list
    if (first == NULL)
    {
      first = newNode;
      last = newNode;
    }
    // list is not empty, so insert at first and make this the new first.  This
    // is the only difference from previous loop
    else
    {
      // so first point the new node to the current first
      newNode->link = first;

      // now we can safely update first to be this new node
      first = newNode; // now newNode is the first node in list
    }
  }

  // after we are done, we can demonstrate loop created list by appending
  // values to end of growing list
  cout << "The list you created by prepending to beginning: " << tostring(first) << endl << endl;

  // ok we are done with that list, we should free it all up
  // hmmm... repeating ourself, this should be a function
  // current = first; // we will delete all nodes from first to last, being careful not to loose our lis
  // while (current != NULL)
  // {
  //   // remember the node we want to delete
  //   NodeType* nodeToDelete = current;

  //   // advance current to next node in list for next iteration of loop
  //   current = current->link;

  //   // now we can safely delete the node because current now know the next
  //   // one in the list
  //   delete nodeToDelete;

  // }
  // // list is now empty, so lets start again
  // first = last = NULL;

  //-----------------------------------------------------------------------
  // Inserting and delete items in the middle of the list
  // Using the list we just previously created.  What if instead of appending
  // or prepending, we wanted to insert a value somewhere in the middle?
  // First you need a pointer to the node that is before where you want to insert
  // Then you create a new node and manipulate the links correctly.

  // Lets say you want to insert after node 2.  We would normally do something like a
  // search first, that returns a pointer to the location where we want to insert.
  // (left as an exercise for the student).
  NodeType* insertAfterThisNode;
  insertAfterThisNode = first->link; // point it to the second node in list

  // crete the new node we will insert
  newNode = new NodeType;
  newNode->info = 42;

  // insert, first the newNode needs to point to what insertAfterThisNode is pointing
  // to
  newNode->link = insertAfterThisNode->link;

  // now we can safely change the link of insertAfterThisNode to point to the new node
  insertAfterThisNode->link = newNode;

  // so did it work?
  cout << "After inserting new value in middle, we have: " << tostring(first) << endl;

  // likwise deleting a node from a linked list is a common and relatively easy
  // task (compared to deleting an item from an array based list).  We can easily
  // chop off the first item
  NodeType* oldFirst = first; // keep track of the first to delete it
  first = first->link;        // chops off the first
  delete oldFirst;            // be good memory managers, no longer needing old first after we chopped
  cout << "After chopping off first, we have: " << tostring(first) << endl;

  // chopping off the last for a singly linked list is a bit more difficult.  For a singly
  // linked list, we usually only keep a pointer to the first and last.  Having a pointer to the
  // last makes inserting a new node after last easy.  But we need a pointer to the item
  // just before the last to make it easy to chop the last.  If we need to do this a lot,
  // we could keep a third pointer besides first and last, nodeBeforeLast, making sure to
  // always keep this pointer as well correctly updated.
  // For our example, I am hardcoding finding the nodeBeforeLast
  NodeType* nodeBeforeLast;
  nodeBeforeLast = first->link->link; // change this if list is not 4 items long

  // so if you can get a pointer to the node before the last, it is then simple to
  // chop the last
  NodeType* oldLast = nodeBeforeLast->link; // keep track of old last to delete it
  nodeBeforeLast->link = NULL;              // we can safely chop now since we saved the old last to delete
  delete oldLast;                           // be good memory managers, no longer need old last after we chop it
  cout << "After chopping off last, we have: " << tostring(first) << endl;

  // And finally delete an item from inside of the list.  This is a little tricker.
  // Lets delete the second item.  We need the item before it, which is the first
  // item or first.  Then we do the following
  // The node before the node we are deleting.  If you point this to the node before
  // where you want to delete, all of the code after will work
  NodeType* nodeBefore = first;
  NodeType* nodeToDelete = nodeBefore->link;
  // we are deleting the second item, the one after first
  nodeBefore->link = nodeToDelete->link; // chop out the nodeToDelete from the list
  delete nodeToDelete;                   // can safely delete the node once we chop it out of list
  cout << "After deleteing the item after first, we have: " << tostring(first) << endl;

  return 0;
}