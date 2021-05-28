/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   February 2, 2019
 * @assg   Dictionary
 *
 * @description An Dictionary class that
 *   implements a key/value store.
 */
#include <iostream>

using namespace std;

#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

/** Dictionary
 * The Dictionary abstract class.  This is an abstract base
 * class.  Pure virtual functions must be implemented
 * by subclasses of this class.
 */
template<typename Key, typename Value>
class Dictionary
{
private:
public:
  Dictionary(){};  // default constructor
  ~Dictionary(){}; // Base destructor

  // pure virtual functions
  virtual void insert(const Key& key, const Value& value) = 0;
  virtual Value find(const Key& key) const = 0;
  virtual void remove(const Key& key) = 0;
  virtual int getSize() const = 0;
};

/** ADictionary
 * A concrete implementatin of a Dictionary key/value store that
 * just uses an array to hold the items for storage.
 */
const int ALLOC_SIZE = 10;
template<typename Key, typename Value>
class ADictionary : public Dictionary<Key, Value>
{
private:
  Key* keys;        // array of the key values
  Value* values;    // array of the corresponding values
  int size;         // the current size of this dictionary
  int currentAlloc; // the current amount of memory allocated

public:
  // constructurs and destructors
  ADictionary();
  ~ADictionary();

  // implement the Dictionary ADT interface
  void insert(const Key& key, const Value& value);
  Value find(const Key& key) const;
  void remove(const Key& key);
  int getSize() const;
};

#endif // DICTIONARY_HPP
