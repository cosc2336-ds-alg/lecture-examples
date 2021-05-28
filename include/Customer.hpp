/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   January 18, 2019
 * @assg   C++ Customers  videos
 *
 * @description A basic customer class to demonstrate use in containers
 */
#include <iostream>
#include <sstream>
#include <string>

#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

using namespace std;

/** Customer
 * A customer for a generic example queuing simulation.
 */
class Customer
{
private:
  int customerNumber;
  int arrivalTime;
  int waitingTime;
  int transactionTime;
  static int nextCustomerId;

public:
  Customer();
  Customer(int arrivalTime, int transactionTime);
  void incrementWaitingTime();
  int getArrivalTime() const;
  int getWaitingTime() const;
  int getTransactionTime() const;
  int getDepartureTime() const;
  string tostring() const;
  friend ostream& operator<<(ostream& out, const Customer& aCustomer);
};

#endif // CUSTOMER_HPP
