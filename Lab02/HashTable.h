#ifndef HASHTABLE_SC_H
#define HASHTABLE_SC_H

/* this is the implementation of a hash table using separate chaining */

#include "HashTableInterface.h"
#include "LinkedList.h"

#include <iostream>
using namespace std;

template <typename ItemType>
class HashTable : public HashTableInterface<ItemType> {
private:
LinkedList<ItemType> *m_hashtable;
static const int DEFAULT_BUCKET_SIZE = 10; 
int m_bucketSize;
int m_numItems;
int hashKey(int searchKey);

public:
HashTable(int bucketSize);
HashTable();
~HashTable();

bool isEmpty() const;
int numItems() const;
// to do: accept a string as a searchKey
bool contains(int searchKey, ItemType item);
bool add(int searchKey, ItemType item);
bool remove(int searchKey, ItemType item);
void printLengths() const;
void printLists() const;

};

template <typename ItemType>
HashTable<ItemType>::HashTable(int bucketSize) : m_bucketSize(bucketSize), m_numItems(0) {
  m_hashtable = new LinkedList<ItemType>[m_bucketSize]; 
}

template <typename ItemType>
HashTable<ItemType>::HashTable() : m_bucketSize(DEFAULT_BUCKET_SIZE), m_numItems(0) {
  m_hashtable = new LinkedList<ItemType>[m_bucketSize];
}

template <typename ItemType>
HashTable<ItemType>::~HashTable() {
  delete [] m_hashtable;
  m_hashtable = nullptr;
}

template <typename ItemType>
int HashTable<ItemType>::hashKey(int searchKey) {
  return (searchKey % m_bucketSize);
}

template <typename ItemType>
bool HashTable<ItemType>::isEmpty() const {
  return m_numItems == 0;
}

template <typename ItemType>
int HashTable<ItemType>::numItems() const {
  return m_numItems;
}

template <typename ItemType>
void HashTable<ItemType>::printLengths() const {
  for (int i = 0; i < m_bucketSize; i++) {
    cout << m_hashtable[i].length() << endl;
  }
}

template <typename ItemType>
void HashTable<ItemType>::printLists() const {
  for (int i = 0; i < m_bucketSize; i++) {
    m_hashtable[i].printList();
  }
}

template <typename ItemType>
bool HashTable<ItemType>::contains(int searchKey, ItemType item) {
  int index = this->hashKey(searchKey);
  return m_hashtable[index].find(item);
}

template <typename ItemType>
bool HashTable<ItemType>::add(int searchKey, ItemType item) {
  int index = this->hashKey(searchKey);
  m_hashtable[index].insertBack(item);
  m_numItems++;
  return true;
}

/* 
removes item from hashtable
returns true if remove worked, false if item not found
*/
template <typename ItemType>
bool HashTable<ItemType>::remove(int searchKey, ItemType item) {
  int index = this->hashKey(searchKey);
  if (m_hashtable[index].find(item)) {
    m_hashtable[index].removeItem(item);
    m_numItems--;
    return true;
  } else {
    return false;
  }
}

#endif
