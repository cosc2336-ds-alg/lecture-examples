/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   March 1, 2019
 * @assg   C++ Queues Applications video
 *
 * @description Example applications of Queues
 *   using our developed Queue ADT.
 */
#include "Customer.hpp"
#include "Queue.hpp"
#include <cassert>
#include <climits>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream> // string streams
#include <string>

using namespace std;

/** random range
 * Return a random number in the given range.  We are given minValue and maxValue,
 * a random integer is generated (with uniform probability) that is between
 * minValue and maxValue (inclusive).
 *
 * @param minValue The minimum value of the range of integers to generate.
 * @param maxValue The maximum of the range of integers to generate.
 *
 * @returns int Returns a random value in range (minValue, maxValue) inclusive
 *   of the end points.
 */
int randomRange(int minValue, int maxValue)
{
  // the range is difference between desired max and min.  We
  // need this magnitude in order to correctly a random value
  // in the given range
  int range = maxValue - minValue + 1;

  // generate a random value in range 0 to range (inclusive)
  int randValue = rand() % range;

  // shift the value so it is in range [minValue, maxValue]
  randValue += minValue;

  return randValue;
}

/** random uniform
 * Return a random floating point value in the range of [0.0, 1.0] with
 * uniform probability of any value in the range being returned.
 */
double randomUniform()
{
  double randValue = (double)rand() / (double)INT_MAX;
  return randValue;
}

//-------------------------------------------------------------------------
/** Customer Queue
 * As in textbook, we'll use inheritance to create a subclass of one of our
 * concrete Queue classes, so that we can add updateWaitingQueue() method
 * for contenience of the simulation.  Normally I would use an STL list,
 * and just write a function to iterate over the customers on the
 * waiting queue.
 */
class CustomerQueue : public LQueue<Customer>
{
public:
  void updateWaitingTimes();
  bool customersAreWaiting();
};

/** update waiting queue
 * The textbook does this in a bad way, as far as I'm concerned.  If we are
 * taking the trouble to make a derived class, lets just iterate over
 * the items on the queue and increment their waiting time if needed.
 */
void CustomerQueue::updateWaitingTimes()
{
  Node<Customer>* temp = queueFront;
  while (temp != NULL)
  {
    temp->item.incrementWaitingTime();
    temp = temp->link;
  }
}

/** CustomerQueue customers waiting
 * Return true if any customers are waiting, false otherwise.
 */
bool CustomerQueue::customersAreWaiting()
{
  return numitems > 0;
}

//-------------------------------------------------------------------------
enum ServerStatus
{
  SERVER_FREE,
  SERVER_BUSY
};

/** Server class
 */
class Server
{
private:
  Customer currentCustomer;
  ServerStatus status;
  int transactionTime;

public:
  Server();
  bool isFree();
  bool isBusy();
  void setFree();
  void setBusy();
  void decreaseTransactionTime();
  int getRemainingTransactionTime();
  Customer getCurrentCustomer();
  void setServerBusy(Customer& customer);
};

/** Server default constructor
 */
Server::Server()
{
  status = SERVER_FREE;
  transactionTime = 0;
}

/** Server isFree
 * Accessor method, return our status, true if FREE,
 * false otherwise.
 */
bool Server::isFree()
{
  return status == SERVER_FREE;
}

/** Server isBusy
 * Accessor method, return our status, true if we are BUSY,
 * false otherwise.
 */
bool Server::isBusy()
{
  return status == SERVER_BUSY;
}

/** Server set free
 *
 */
void Server::setFree()
{
  status = SERVER_FREE;
}

/** Server set to busy
 *
 */
void Server::setBusy()
{
  status = SERVER_BUSY;
}

/** Server decrease transaction time
 * Decrement the transaction time to simulate that we
 * are in process of serving a customer with their request.
 */
void Server::decreaseTransactionTime()
{
  transactionTime--;
}

/** Server getRemainingTransactionTime
 * Return the amount of remaining transaction time we currently have
 * yet to process.
 */
int Server::getRemainingTransactionTime()
{
  return transactionTime;
}

/** Server get current customer
 */
Customer Server::getCurrentCustomer()
{
  return currentCustomer;
}

/** Server give customer
 * Set the Server busy processing a given customer
 */
void Server::setServerBusy(Customer& customer)
{
  currentCustomer = customer;
  transactionTime = currentCustomer.getTransactionTime();
  setBusy();
}

/** ServerList
 */
class ServerList
{
private:
  int numOfServers;
  Server* server;

public:
  ServerList(int numOfServers = 1);
  void updateServers();
  bool serversAreFree();
  void assignCustomer(Customer& customer);
};

/** ServerList constructor
 *
 */
ServerList::ServerList(int numOfServers)
{
  this->numOfServers = numOfServers;
  server = new Server[numOfServers];
}

/** ServerList update
 * Simulate servers handling/updating customer transactions
 */
void ServerList::updateServers()
{
  // Check each server
  for (int sid = 0; sid < numOfServers; sid++)
  {
    // if server is busy, simulate it processing transaction, and
    // check if it is actually now done with it transaction
    if (server[sid].isBusy())
    {
      server[sid].decreaseTransactionTime();

      // check if this server has completed the transaction
      if (server[sid].getRemainingTransactionTime() == 0)
      {
        Customer customer = server[sid].getCurrentCustomer();

        cout << "From server number " << (sid + 1) << endl
             << "   customer: " << customer << endl
             << "   departed at time: " << customer.getDepartureTime() << endl;

        // the server is now free
        server[sid].setFree();
      }
    }
  }
}

/** ServerList free servers
 * Return true if there are servers currently free to server customers.
 */
bool ServerList::serversAreFree()
{
  for (int sid = 0; sid < numOfServers; sid++)
  {
    if (server[sid].isFree())
    {
      return true;
    }
  }

  // if we got to this point, no servers were FREE, so the ansewer is false,
  return false;
}

/** ServerList assign customer
 * Assign the customer to a free server.  This function should not be called
 * unless it is already known that a server is free.
 */
void ServerList::assignCustomer(Customer& customer)
{
  // assign to next free server
  for (int sid = 0; sid < numOfServers; sid++)
  {
    if (server[sid].isFree())
    {
      server[sid].setServerBusy(customer);
      return;
    }
  }

  // if we get to this point, it means that a customer
  // was popped from the wait queue, but no server was
  // actually available to serve, panic!
  cerr << "<ServerList::assignCustomer> no free servers for customer!" << endl;
  assert(false);
}

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
  // simulation parameters, we could input these from user or file
  const int SIM_TIME = 100; // total system time to simulate
  const int NUM_SERVERS = 3;
  const int MIN_TRANSACTION_TIME = 4;
  const int MAX_TRANSACTION_TIME = 6;
  const float CUSTOMER_ARRIVAL_PROB = 0.9; // probability of customers arriving

  // our customer queue and list of servers
  CustomerQueue waitQueue;
  ServerList servers(NUM_SERVERS);

  // statistics of the simulation
  int totalWaitTime = 0;
  int totalCustomersArrived = 0;
  int totalCustomersServed = 0;

  srand(time(0)); // seed random number generator using current time

  cout << "Running queuing simulation" << endl << endl;
  int time = 1;
  while (time <= SIM_TIME || waitQueue.customersAreWaiting())
  {
    cout << "Simulation time: " << time << endl;

    // Determine if a new customer arrives during this time period
    // approximate Poisson arrival probability
    if (time <= SIM_TIME)
    {
      if (randomUniform() > exp(-CUSTOMER_ARRIVAL_PROB))
      {
        int transactionTime = randomRange(MIN_TRANSACTION_TIME, MAX_TRANSACTION_TIME);
        Customer customer(time, transactionTime);
        waitQueue.enqueue(customer);
        totalCustomersArrived++;
      }
    }

    // check for waiting customers and assign to free servers
    // a little tricky so added explicit convenience methods to both our customer queue
    // and server list.  So if customers are waiting and servers are free, we should
    // get the next customer and assign them to a free server
    while (waitQueue.customersAreWaiting() && servers.serversAreFree())
    {
      // take customer from the head of the queue
      Customer customer = waitQueue.front();
      waitQueue.dequeue();

      // assign customer to a free server
      totalCustomersServed++;
      totalWaitTime += customer.getWaitingTime();
      servers.assignCustomer(customer);
    }

    // Display current status of wait queue
    // cout << waitQueue << endl;

    // Update waiting times of waiting customers
    waitQueue.updateWaitingTimes();

    // Update any current server/customer transactions
    servers.updateServers();

    // update system time for next iteration
    time++;
  }

  cout << "Simulation Finished:" << endl;
  cout << "    total customer arrivals: " << totalCustomersArrived << endl;
  cout << "    total customers served : " << totalCustomersServed << endl;
  cout << "    total waiting time     : " << totalWaitTime << endl;
  double averageWaitTime = (double)totalWaitTime / (double)totalCustomersServed;
  cout << "    average waiting time   : " << averageWaitTime << endl;

  return 0;
}
