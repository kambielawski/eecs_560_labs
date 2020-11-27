#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include <string>
#include <iostream>
using namespace std;

class Executive {
private:
ifstream &m_infile;

public:
Executive(ifstream& infile);
~Executive();
void run();

};

Executive::Executive(ifstream& infile) : m_infile(infile) {
  string word;
  while (m_infile >> word) {
    cout << word << endl;
  }
}

Executive::~Executive() {}

void Executive::run() {
  cout << "running!" << endl;
}

#endif
