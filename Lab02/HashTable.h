#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "LinkedList.h"

template <typename ItemType>
class ChainedHashTable : public HashTableInterface {
private:
LinkedList<ItemType> *m_hashtable;

public:
ChainedHashTable();
~ChainedHashTable();

};

ChainedHashTable<ItemType>::ChainedHashTable() {

};

#endif
