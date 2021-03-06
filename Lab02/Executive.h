#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include <string>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "HashTable.h"
using namespace std;

struct PlayerEntry {
  int numGoals;
  string playerName;

  bool operator==(const PlayerEntry& rhs) {
    return (numGoals == rhs.numGoals && playerName == rhs.playerName);
  }
};

ostream& operator << (ostream& o, const PlayerEntry& rhs) {
  return o << rhs.playerName << " " << rhs.numGoals;
}

class Executive {
private:
ifstream &m_infile;
HashTable<PlayerEntry> m_hashtable;
void readFileIntoHashTable(ifstream& infile);
void printMenu() const;

public:
Executive(ifstream& infile);
~Executive();
void run();
void addPlayer();
void removePlayer();
void printPlayersList() const;
void playersWithEqualTo();
void playersWithGreaterThan();
void playersWithLessThan();
int getInt(std::istream& stream) const;
PlayerEntry parsePlayerEntry(string playerEntry) const;

};

Executive::Executive(ifstream& infile) : m_infile(infile) {
  this->readFileIntoHashTable(m_infile);
}

Executive::~Executive() {}

void Executive::run() {
  int choice;
  while (choice != 7) {
    this->printMenu();
    choice = this->getInt(cin);
  
    switch(choice) {
      case 1: 
        this->addPlayer();
        break;
      case 2:
        this->removePlayer();
        break;
      case 3:
        this->printPlayersList();
        break;
      case 4:
        this->playersWithEqualTo();
        break;
      case 5:
        this->playersWithGreaterThan();
        break;
      case 6:
        this->playersWithLessThan();
        break;
      case 7:
        cout << "Exiting...\n";
        break;
      default:
        cout << "Please enter a number between 1-7\n";
        break;
    }
    cout << "--------------------\n";
  }
}

/* 
Gets an integer from an istream object
*/
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

PlayerEntry Executive::parsePlayerEntry(string playerEntry) const {
  PlayerEntry newPlayer; 
  // remove whitespace
  playerEntry.erase(remove(playerEntry.begin(), playerEntry.end(), ' '), playerEntry.end());
  // split string on index of colon
  int indexOfColon = playerEntry.find(':');

  if (indexOfColon != -1) {
    string playerName = playerEntry.substr(0, indexOfColon);
    string numGoalsStr = playerEntry.substr(indexOfColon+1);
    int numGoals;
    // convert numGoalsStr to (int) numGoals
    try {
      numGoals = stoi(numGoalsStr);
    } catch (exception& e) {
      throw std::runtime_error("Could not parse number of goals to an integer"); 
    }

    newPlayer.playerName = playerName;
    newPlayer.numGoals = numGoals;
  } else {
    throw std::runtime_error("Entry could not be parsed. Format: <Player Name>: <Number of Goals>");
  }
  
  return newPlayer;
}

void Executive::readFileIntoHashTable(ifstream& infile) {
  string playerEntryString;
  while (!infile.eof()) {
    getline(infile, playerEntryString, ',');
    PlayerEntry playerEntry = parsePlayerEntry(playerEntryString);
    m_hashtable.add(playerEntry.numGoals, playerEntry);
  }
}

void Executive::printMenu() const {
  cout << "Please choose one of the following commands:\n"
  << "1- AddPlayer\n"
  << "2- RemovePlayer\n"
  << "3- PrintPlayersList\n"
  << "4- PlayerWithGoalCountEqualTo(g)\n"
  << "5- PlayerWithNumGoalsGreaterThan(h)\n"
  << "6- PlayerWithNumGoalsLessThan(i)\n"
  << "7- Exit\n\n"
  << "Input: ";
}


void Executive::addPlayer() {
  PlayerEntry player;
  string playerEntryString;
  cout << "Enter the record to be inserted: ";
  getline(cin, playerEntryString);
  try {
    player = this->parsePlayerEntry(playerEntryString);
  } catch (exception& e) {
    cout << "Failed to successfully insert record:\n" << e.what() << endl;
  }
  if (m_hashtable.add(player.numGoals, player)) {
    cout << "Record successfully inserted\n";
  }
}

void Executive::printPlayersList() const { 
  m_hashtable.printLists();
}

void Executive::removePlayer() {
  PlayerEntry player;
  string playerEntryString;
  cout << "Enter the record to be removed: ";
  getline(cin, playerEntryString);
  try {
    player = this->parsePlayerEntry(playerEntryString);
  } catch (exception& e) {
    cout << "Failed to successfully remove record:\n" << e.what() << endl;
  }
  if (m_hashtable.remove(player.numGoals, player)) {
    cout << "Record successfully removed\n";
  } else {
    cout << "Could not find record '" << playerEntryString << "'\n";
  }
}

bool greaterThan(PlayerEntry player, int comp) {
  return player.numGoals > comp;
}
bool lessThan(PlayerEntry player, int comp) {
  return player.numGoals < comp;
}
bool equalTo(PlayerEntry player, int comp) {
  return player.numGoals == comp;
}
void printPlayerName(PlayerEntry player) {
  cout << player.playerName << endl;
}

void Executive::playersWithGreaterThan() {
  cout << "Enter goal count: ";
  int goalCount = this->getInt(cin);
  
  m_hashtable.traverseTable(greaterThan, goalCount, printPlayerName);
}

void Executive::playersWithLessThan() {
  cout << "Enter goal count: ";
  int goalCount = this->getInt(cin);
  
  m_hashtable.traverseTable(lessThan, goalCount, printPlayerName);
}

void Executive::playersWithEqualTo() {
  cout << "Enter goal count: ";
  int goalCount = this->getInt(cin);
  
  m_hashtable.traverseTable(equalTo, goalCount, printPlayerName);
}


#endif
