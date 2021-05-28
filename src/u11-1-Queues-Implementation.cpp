/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   March 1, 2019
 * @assg   C++ Queues Implementation video
 *
 * @description Introduction to Queues.
 *   A Queue ADT.
 */
#include "Queue.hpp"
#include <iomanip>
#include <iostream>
#include <sstream> // string streams
#include <string>

using namespace std;

//-------------------------------------------------------------------------
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
  // Test array based queue -----------------------------------------------
  cout << "---------- Testing array based queue ----------------------------" << endl;
  AQueue<string> aQueue;

  // test isEmpty
  cout << boolalpha << "Is aQueue empty? " << aQueue.isEmpty() << endl;
  cout << aQueue << endl;
  cout << endl;

  // test add some items.
  aQueue.enqueue("Derek");
  aQueue.enqueue("Susan");
  aQueue.enqueue("Alan");

  // test front
  cout << aQueue << endl;
  cout << "My front item: " << aQueue.front() << endl;
  cout << boolalpha << "Is aQueue empty? " << aQueue.isEmpty() << endl;
  cout << "Queue length: " << aQueue.length() << endl;
  cout << endl;

  // test remove
  aQueue.dequeue();
  aQueue.dequeue();
  cout << aQueue << endl;
  cout << "My front item: " << aQueue.front() << endl;
  cout << endl;

  // test front from empty queue
  aQueue.dequeue();
  cout << boolalpha << "Is aQueue empty? " << aQueue.isEmpty() << endl;
  cout << aQueue << endl;
  try
  {
    aQueue.front();
  }
  catch (EmptyQueueException emptyQueueObj)
  {
    cout << "Caught expected EmptyQueueException: " << endl << emptyQueueObj.what() << endl << endl;
  }

  // test dequeue from empty queue
  try
  {
    aQueue.dequeue();
  }
  catch (EmptyQueueException emptyQueueObj)
  {
    cout << "Caught expected EmptyQueueException: " << endl << emptyQueueObj.what() << endl << endl;
  }

  // test queue growth
  for (int i = 0; i < 120; i++)
  {
    aQueue.enqueue("Queue Item " + to_string(i));
  }
  cout << "Queue length after pushing lots of items: " << aQueue.length() << endl;
  cout << aQueue << endl;

  // Test list based queue ------------------------------------------------
  cout << "---------- Testing list based queue ----------------------------" << endl;
  LQueue<double> lQueue;

  // test isEmpty
  cout << boolalpha << "Is lQueue empty? " << lQueue.isEmpty() << endl;
  cout << lQueue << endl << endl;

  // test enqueue some items.
  lQueue.enqueue(4.2);
  lQueue.enqueue(-3.0e-15);
  lQueue.enqueue(42e42);

  // test front
  cout << lQueue << endl << endl;
  cout << "My front item: " << lQueue.front() << endl;
  cout << boolalpha << "Is lQueue empty? " << lQueue.isEmpty() << endl;
  cout << "My queue length: " << lQueue.length() << endl;
  cout << endl;

  // test dequeue
  lQueue.dequeue();
  lQueue.dequeue();
  cout << lQueue << endl;
  cout << "My front item: " << lQueue.front() << endl;
  cout << endl;

  // test front from empty queue
  lQueue.dequeue();
  cout << boolalpha << "Is lQueue empty? " << lQueue.isEmpty() << endl;
  cout << lQueue << endl;
  try
  {
    lQueue.front();
  }
  catch (EmptyQueueException emptyQueueObj)
  {
    cout << "Caught expected EmptyQueueException: " << endl << emptyQueueObj.what() << endl << endl;
  }

  // test dequeue from empty queue
  try
  {
    lQueue.dequeue();
  }
  catch (EmptyQueueException emptyQueueObj)
  {
    cout << "Caught expected EmptyQueueException: " << endl << emptyQueueObj.what() << endl << endl;
  }

  return 0;
}
