/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  CSci 520, Spring 2022
 * @ide    VSCode Server
 * @date   January 24, 2022
 * @assg   List Reversal
 *
 * @description Sedgwick text, program 3.10 
 *   Example unction to reverse a list.
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

/** @brief list reversal
 *
 * Example function to reverse a list.  We are given the head of the original
 * list as input.  We keep 3 pointers to the previous, current and next node.
 * This function destructively repoints the original list.  The new head
 * (old tail) is returned from this function.
 *
 * @param head The head of the current list to be reversed in place.
 *
 * @return Node* Returns a pointer to the new head of the list, which was the
 *   original tail node.  This new list has been repointed to reverse the
 *   items of the original list.
 */
Node* reverseList(Node* oldHead)
{
  Node* prev = nullptr;
  Node* current = oldHead;
  Node* next = nullptr;

  // the current node is the one we are currently working on repointing.
  // keep doing work while current is not the nullptr indicating we have
  // finished processing
  while (current != nullptr)
  {
    // remember the next node and point current node to previous node
    next = current->next;
    current->next = prev;

    // update previous and current for next iteration
    prev = current;
    current = next;
  }

  // return new head, which the previous node will be left point at
  return prev;
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
    cerr << "Usage: g03-10 N" << endl;
    exit(0);
  }
  int N = atoi(argv[1]);
  
  // construct a linked list of N random items
  int item = rand() % 1000;
  Node* head = new Node(item, nullptr);
  Node* temp = head;
  for (int itemNum = 1; itemNum <= N-1; itemNum++)
  {
    item = rand() % 1000;
    temp->next = new Node(item, nullptr);
    temp = temp->next;
  }


  // display the list before reversing
  cout << "Random list before reversing the list" << endl;
  cout << listToString(head) << endl;
  cout << endl;

  // do the list reversal, the new head is returned so remember
  // the new head of the reversed list
  head = reverseList(head);
  
  // display the list after reversing
  cout << "Random list after reversing the list" << endl;
  cout << listToString(head) << endl;
  cout << endl;

}
