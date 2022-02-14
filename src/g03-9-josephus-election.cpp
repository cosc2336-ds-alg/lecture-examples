/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  CSci 520, Spring 2022
 * @ide    VSCode Server
 * @date   January 24, 2022
 * @assg   Josephus Election
 *
 * @description Sedgwick text, program 3.9 Josephus Election.
 *   Given a circular linked list arrangement of N people,
 *   elect a volunteer by skipping to every Mth person who
 *   removes themselves from consideration.  Last remaining
 *   person is "it".
 */
#include <iostream>
using namespace std;


/** @brief node
 *
 * Basic node strucutre for singly linked list.
 */
struct Node
{
  int id;
  Node* next;

  // constructor to create a new node pointing to next item
  Node(int id, Node* next)
  {
    this->id = id;
    this->next = next;
  }
};


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
  if (argc != 3)
  {
    cerr << "Error: expected command line arguments specifying N number of people and M number of skips" << endl;
    cerr << "Usage: g03-9 N m" << endl;
    exit(0);
  }
  int N = atoi(argv[1]);
  int M = atoi(argv[2]);
  
  // create initial circular list of a single node with person id of 1
  Node* head = new Node(1, nullptr);
  head->next = head;
  Node* tmp = head;

  // now add in nodes to represent the people with ids 2 thorugh N to the list
  for (int id = 2; id <= N; id++)
  {
    // create new node and point heads next node to the new node.
    // notice the new node is set to point to the tail
    head->next = new Node(id, tmp);

    // repoint head to the new node we just created for next loop iteration
    head = head->next;
  }

  // now perform a josephus election.  We skip M-1 nodes and remove the node from
  // the list.  We are done when there is only 1 node left, which we detect by
  // determining that our head node points to itself
  cout << "Victims: ";
  while (head != head->next)
  {
    // select the next M-1^{th} victim in remaining candidates, first search
    // for the (M-1)^{th} person
    for (int victim = 1; victim < M; victim++)
    {
      head = head->next;
    }

    // head now points to the next victim, which we remove from the list
    // unlike the text we remove and deallocate the memory
    tmp = head->next;
    cout << " " << tmp->id;
    head->next = tmp->next;
    delete tmp;
  }

  // display the survivor
  cout << endl;
  cout << "Survivor: " << head->id << endl;
  
}
