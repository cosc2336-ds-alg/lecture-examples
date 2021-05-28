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
#include "Dictionary.hpp"
#include "Employee.hpp"
using namespace std;

/**
 *
 */
template<typename Key, typename Value>
ADictionary<Key, Value>::ADictionary()
{
  size = 0;
  keys = new Key[ALLOC_SIZE];
  values = new Value[ALLOC_SIZE];
  currentAlloc = ALLOC_SIZE;
}

/**
 *
 */
template<typename Key, typename Value>
ADictionary<Key, Value>::~ADictionary()
{
  delete[] keys;
  delete[] values;
}

/**
 *
 */
template<typename Key, typename Value>
void ADictionary<Key, Value>::insert(const Key& key, const Value& value)
{
  // what about duplicate keys?  Many key/value dictionaries require keys
  // to be unique, thus insertion of a duplicate would cause an error, or
  // would replace the old key with the new one

  // add the item to the end of our keys/values arrays
  keys[size] = key;
  values[size] = value;
  size++;
}

/**
 *
 */
template<typename Key, typename Value>
Value ADictionary<Key, Value>::find(const Key& key) const
{
  // perform linear search on the array to find the key
  for (int index = 0; index < size; index++)
  {
    if (keys[index] == key)
    {
      return values[index];
    }
  }

  // otherwise error, we should throw an exception or something
  // here, instead we just display a message to illustrate
  cerr << "<ADictionary::find()> Error: key not found: " << key << endl;
  Value unknown{}; // will use default constructor to create and return something
  return unknown;
}

/**
 *
 */
template<typename Key, typename Value>
void ADictionary<Key, Value>::remove(const Key& key)
{
  // search for the key location
  int location = 0;
  bool found = false;
  while ((location < size) and (not found))
  {
    if (keys[location] == key)
    {
      found = true;
    }
    else
    {
      location++;
    }
  }

  // if not found, we should throw an exception or something, but we
  // just display an error message
  if (not found)
  {
    cerr << "ADictionary::remove()> Error: key not found: " << key << endl;
  }

  // otherwise remove the item by shifting all higher items down, so we
  // don't have to deal with missing holds or special flags for key
  // values to indicate empty
  for (int index = location; index < size; index++)
  {
    keys[index] = keys[index + 1];
    values[index] = values[index + 1];
  }
  size--;
}

/**
 *
 */
template<typename Key, typename Value>
int ADictionary<Key, Value>::getSize() const
{
  return size;
}

/**
 * @brief Cause specific instance compilations
 *
 * This is a bit of a kludge, but we can use normal make dependencies
 * and separate compilation by declaring template class
 * Dictionary<needed_type> here of any types we are going to be
 * instantianting with the template.
 *
 * https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
 * https://isocpp.org/wiki/faq/templates#separate-template-class-defn-from-decl
 */
template class ADictionary<string, float>;
template class ADictionary<int, Employee>;
