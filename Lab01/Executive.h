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
LinkedList<int> m_list;
void displayMenu() const;
void readFileIntoList();

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

  while (input != "11") {
    this->displayMenu();
    try {
      std::getline(cin, input);
      choice = stoi(input);
    } catch (exception& e) {
      cout << "\n----------------\n";
      cout << "invalid input: input must be an integer between 1-11";
      cout << "\n----------------\n";
      continue;
    }

    cout << "\n----------------\n";
    switch (choice) {
      case 1: cout << "Is Empty: " << m_list.isEmpty();
        break;
      case 2: cout << "Length: " << m_list.length(); 
        break;
      case 3: 
        break;
      case 4: 
        break;
      case 5: 
        break;
      case 6: 
        break;
      case 7:  
        break;
      case 8: 
        cout << "List: ";
        m_list.printList();
        break;
      case 9: 
        cout << "Reversed list:";
        m_list.printListReverse();
        break;
      case 10: 
        break;
      case 11: cout << "Exiting...";
        break;
      default: cout << "Invalid input. Enter a number between 1-11";
        break;
    }
    cout << "\n----------------\n";
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
  << "Input:";
}

#endif
