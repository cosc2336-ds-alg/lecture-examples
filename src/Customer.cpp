/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   January 18, 2019
 * @assg   C++ Queues videos
 *
 * @description A basic Customer class to demonstrate use
 *   in containers.
 */
#include "Customer.hpp"
#include <iostream>
using namespace std;

// class global to keep track of and assign
// Customer ids
int Customer::nextCustomerId = 1;

/** Customer default constructor
 */
Customer::Customer()
{
  this->customerNumber = 0;
  this->arrivalTime = 0;
  this->waitingTime = 0;
  this->transactionTime = 0;
}

/** Customer constructor
 */
Customer::Customer(int arrivalTime, int transactionTime)
{
  this->customerNumber = nextCustomerId++;
  this->arrivalTime = arrivalTime;
  this->waitingTime = 0;
  this->transactionTime = transactionTime;
}

/** Customer arrival time accessor
 */
int Customer::getArrivalTime() const
{
  return arrivalTime;
}

/** Customer wait time accessor
 */
int Customer::getWaitingTime() const
{
  return waitingTime;
}

/** Customer transactionTime accessor
 */
int Customer::getTransactionTime() const
{
  return transactionTime;
}

/** Customer departure time accessor
 */
int Customer::getDepartureTime() const
{
  return arrivalTime + waitingTime + transactionTime;
}

/** increment waiting time
 */
void Customer::incrementWaitingTime()
{
  waitingTime++;
}

/** Customer tostring
 */
string Customer::tostring() const
{
  ostringstream out;

  // out << "Customer num: " << customerNumber << endl
  //    << "        arrival time: " << arrivalTime << endl
  //    << "        waiting time: " << waitingTime << endl
  //    << "    transaction time: " << transactionTime << endl;
  out << "id: " << customerNumber << " (arrive: " << arrivalTime << " wait: " << waitingTime << " trans: " << transactionTime << ")"
      << " depart: " << getDepartureTime() << ")";

  return out.str();
}

/** Customer output stream operator
 */
ostream& operator<<(ostream& out, const Customer& aCustomer)
{
  out << aCustomer.tostring();
  return out;
}
