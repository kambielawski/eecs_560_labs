#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include <iostream>
#include <fstream>
#include <string>
#include <exception>

#include "LinkedList.h"

using namespace std;

class Executive {
private:
ifstream m_infile;
void displayMenu() const;

public:
Executive(char *fileName);
~Executive();

void run();
};

Executive::Executive (char *fileName) {
  m_infile.open(fileName);
  if (m_infile.is_open()) {
    cout << "file open!" << endl;
  } else {
    throw runtime_error("couldn't open file");
  }
}

Executive::~Executive() {}

void Executive::run() {
  LinkedList<char> list;
  this->displayMenu();
  list.insertBack('a');
  list.insertBack('b');
  list.insertBack('c');

  list.printList();
  list.printListReverse();
}

void Executive::displayMenu() const {
  cout << "Choose one operation from the options below:\n\n"
  << "1. Is Empty\n"
  << "2. Length\n"
  << "3. Insert\n"
  << "4. Delete\n"
  << "5. Delete Duplicates\n"
  << "6. Find\n"
  << "7. Find Next\n"
  << "8. Print\n"
  << "9. Reverse List\n"
  << "10. Print At\n"
  << "11. Exit\n";
}

#endif
