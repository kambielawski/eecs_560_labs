#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include <string>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "HashTable.h"
using namespace std;

class Executive {
private:
ifstream &m_infile;
HashTable<string> m_hashtable;
void readFileIntoHashTable(ifstream& infile);

public:
Executive(ifstream& infile);
~Executive();
void run();

};

Executive::Executive(ifstream& infile) : m_infile(infile) {
  this->readFileIntoHashTable(m_infile);
}

Executive::~Executive() {}

void Executive::run() {
  cout << "running!" << endl;
}

void Executive::readFileIntoHashTable(ifstream& infile) {
  string entry;
  string numGoalsStr;
  int numGoals;
  while (!infile.eof()) {
    getline(infile, entry, ':');
    getline(infile, numGoals, ',');
    // remove whitespace
    entry.erase(remove(entry.begin(), entry.end(), ' '), entry.end());
    numGoalsStr.erase(remove(numGoalsStr.begin(), numGoalsStr.end(), ' '), numGoalsStr.end());
    // convert numGoalsStr to int
    try {
      numGoals = stoi(numGoalsStr);
    } catch (exception& e) {
      throw e;
    }
    m_hashtable.add(numGoals, entry);
  }
}

#endif
