/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  CSci 520, Spring 2022
 * @ide    VSCode Server
 * @date   January 24, 2022
 * @assg   List Insertion Sort
 *
 * @description Sedgwick text, program 3.10 
 *   Example of sorting a list.  We generate random integers and insert the
 *   values into a list, maintaining the list in sorted order.
 */
#include <cstdlib>
#include <iostream>
#include <sstream>
using namespace std;


/** @brief node
 *
 * Basic node strucutre for singly linked list.
 */
struct Node
{
  int item;
  Node* next;

  // constructor to create a new node pointing to next item
  Node(int id, Node* next)
  {
    this->item = id;
    this->next = next;
  }
};


/** @brief display linked list
 *
 * Given a pointer to the head of a singly linked list, display the
 * items in the linked list.  We assume that the last node of the
 * linked list links to the nullptr to detect when we have
 * fully traversed the linked list.
 *
 * @param node A pointer to  Node structure, the initial node we are
 *   to traverse to display the contents of this list.
 */
string listToString(Node* node)
{
  ostringstream out;

  // iterate over the items in the linked list
  out << "Head:";
  while (node != nullptr)
  {
    out << " " << node->item;
    node = node->next;
  }
  out << " :Tail";

  // return the string we constructed
  return out.str();
}


/** @brief sort list
 * 
 * Using an insertion sort, take an original list of values in no order and
 * insert them into sorted order into a new list.  This function is destructive
 * of the original list. We reuse the nodes of the original list, simply repointing
 * the links to put the list into a sorted order.
 * 
 * @param randomHead The head of the input list we are given to sort.
 *
 * @return Node* Return a link to the new head of the list that is now sorted.
 */
Node* sortList(Node* randomHead)
{
  // initially the sorted list is empty
  Node* sortedHead = nullptr;

  // we insert the first node into sorted list by hand to get things started and avoid
  // having to use a dummy head as text does.  Note we are explicitly assuming that
  // the input random list is not empty here, if it could be empty we should be checking
  // for that
  sortedHead = randomHead;
  Node* current = randomHead->next;
  sortedHead->next = nullptr;

  // iterate over the old list, inserting the nodes into the sorted list at
  // correct position
  Node* next = nullptr;
  while (current != nullptr)
  {
    cout << "Sorting item: " << current->item << endl;
    
    // keep track of next node in original list for next iteration of loop
    next = current->next;

    // search for position to correctly insert current node into sorted list.
    // after loop the insertNode pointer should be pointing to node before where
    // we need to insert the current node
    Node* insertNode = sortedHead;
    while (insertNode->next != nullptr)
    {
      // see if the next item is bigger than the current item, and if so we found
      // the position for insertion
      cout << "Testing next item: " << insertNode->next->item << endl;
      if (insertNode->next->item > current->item)
      {
	// when found we immediately break out of loop to stop the search
	break;
      }

      // otherwise keep searching
      insertNode = insertNode->next;
    }
    cout << "Ended search" << endl << endl;
    
    // at this point, insertNode should point to node after which we need to insert
    // the current node.  Though if the node needs to be the new head node, then
    // insertNode is incorrect, we check that now
    if (randomHead->item > current->item)
    {
      current->next = sortedHead;
      sortedHead = current;
    }
    else
    {
      current->next = insertNode->next;
      insertNode->next = current;
    }

    // and now move current to the next node.
    // NOTE: this was the original next node that we kept track of, before we modified
    // current to insert it into the linked list
    current = next;
  }

  // return the head of the newly sorted list
  return sortedHead;
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
  // parse command line arguments to determine number of primes to search
  if (argc != 2)
  {
    cerr << "Error: expected command line arguments specifying N number of random items to generate for linked list" << endl;
    cerr << "Usage: g03-11 N" << endl;
    exit(0);
  }
  int N = atoi(argv[1]);
  
  // construct a linked list of N random items
  int item = rand() % 1000;
  Node* randomHead = new Node(item, nullptr);
  Node* temp = randomHead;
  for (int itemNum = 1; itemNum <= N-1; itemNum++)
  {
    item = rand() % 1000;
    temp->next = new Node(item, nullptr);
    temp = temp->next;
  }

  // display the list before sorting
  cout << "Random list before sorting the list" << endl;
  cout << listToString(randomHead) << endl;
  cout << endl;

  Node* sortedHead;
  sortedHead = sortList(randomHead);

  // display the list after sorting
  cout << "List after insertion sort of the list" << endl;
  cout << listToString(sortedHead) << endl;
  cout << endl;
}
