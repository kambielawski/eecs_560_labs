#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <climits>
#include <exception>

#include "LinkedList.h"

using namespace std;

class Executive {
private:
ifstream m_infile;
LinkedList<int> m_list;
void displayMenu() const;
void readFileIntoList();
int getInt(std::istream& stream) const;
void insertIntoList();
void deleteFromList();
void printItemAtIndex() const;
void findItemInList() const;

public:
Executive(char *fileName);
~Executive();

void run();
};

Executive::Executive (char *fileName) {
  m_infile.open(fileName);
  if (m_infile.is_open()) {
    this->readFileIntoList();
  } else {
    throw runtime_error("couldn't open file");
  }
}

Executive::~Executive() {}

void Executive::run() {
  string input; 
  int choice;

  while (choice != 11) {
    this->displayMenu();
    choice = this->getInt(cin);

    cout << "\n----------------\n";
    switch (choice) {
      case 1: cout << "Is Empty: " << m_list.isEmpty();
        break;
      case 2: cout << "Length: " << m_list.length(); 
        break;
      case 3: this->insertIntoList();
        break;
      case 4: this->deleteFromList(); // delete
        break;
      case 5: // delete duplicates
        break;
      case 6: this->findItemInList(); 
        break;
      case 7: // find next
        break;
      case 8: 
        cout << "List: ";
        m_list.printList();
        break;
      case 9: 
        cout << "Reversed list:";
        m_list.printListReverse();
        break;
      case 10: this->printItemAtIndex();
        break;
      case 11: cout << "Exiting...";
        break;
      default: cout << "Invalid input. Enter a number between 1-11";
        break;
    }
    cout << "\n----------------\n";
  }
}

int Executive::getInt(std::istream& stream) const {
  string input;
  int value;
  bool loop = true;

  while (loop) {
    std::getline(stream, input);
    std::stringstream linestream(input);

    if (!(linestream >> value)) {
      cout << "Invalid input. Enter an integer.\n";
      continue; // input was not an integer
    } else {
      loop = false;
    }
  }
  return value;
}

void Executive::insertIntoList() {
  string input;
  int newItem;

  while (input != "x") {
    cout << "Choose a number to be inserted: ";
    std::getline(cin, input);
    try {
      newItem = stoi(input);
      m_list.insertFront(newItem);
      cout << newItem << " has been inserted";
      break;
    } catch (exception& e) {
      if (input != "x")
        cout << "Invalid input. Input must be an integer. (enter 'x' to cancel)\n";
    }
  }
}

void Executive::deleteFromList() {
  string input;
  int itemToBeDeleted;

  while (input != "x") {
    cout << "Choose a number to be deleted from the list: ";
    std::getline(cin, input);
    try {
      itemToBeDeleted = stoi(input);
      if (m_list.find(itemToBeDeleted)) {
        m_list.removeItem(itemToBeDeleted);
        cout << itemToBeDeleted << " has been deleted.";
        break;
      }
      else 
        cout << itemToBeDeleted << " is not in the list. Deleted nothing.";
    } catch (exception& e) {
      if (input != "x")
        cout << "Invalid input. Input must be an integer. (enter 'x' to cancel)\n";
    }
  }
}

void Executive::printItemAtIndex() const {
  int index;
  bool validIndex = false;

  while (!validIndex) {
    cout << "Enter an integer: ";
    index = this->getInt(cin);
    if (index < 0 || index > m_list.length() - 1) {
      cout << "Index out of list range.\n";
    } else {
      validIndex = true;
      cout << "Item at index " << index << " is " << m_list.getItemAtIndex(index);
    }
  }
}

void Executive::findItemInList() const {
  int itemToFind;
  cout << "Enter an item to find: ";
  itemToFind = this->getInt(cin);
  if (m_list.find(itemToFind)) {
    cout << itemToFind << " is in the list";
  } else {
    cout << itemToFind << " is not in the list";
  }
}

void Executive::readFileIntoList() {
  string line;
  int num;
  while (std::getline(m_infile, line)) {
    num = stoi(line);
    m_list.insertFront(num);
  }
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
  << "11. Exit\n\n"
  << "Input: ";
}

#endif
