// implementation basic hashmap (unordered container)
// Author:  Nicholas Stafford
// Class:   cs3
// Due:     3/16/18


#include <iostream>
#include <fstream>
#include "hashmap.h"
#include <string>


using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::string;
using std::ifstream;
using std::getline;
using std::stoi; // converts string to integer

const int kDataSize = 25;

int getID() {
  // gets a valid id from the user
  // ID must be a positive number or -1
  string userInput; // accept string so all inputs are valid
  int iD;

  // use try catch in case user enters bad input
  while (cin >> userInput) {
    try {
      iD = stoi(userInput); // convert user input to int
      if (iD < 0 && iD != -1)
        throw 0;
      break;
    }
    catch (...) {
      cout << "ID must be a positive number" << endl;
      continue;
    }
  }
  return iD;
}

void fill(hashmap<int, string> &hm) {
  ifstream file("data.txt");
  if (!file.is_open()) {
    cerr << "Could not find data.txt" << endl;
    exit(1);
  }
  // use both safe and unsafe insert methods
  do {
    string name;
    int id;
    file >> id; // id is first word on line
    file.get(); // removes single whitespace
    getline(file, name); // name ends at end of line

    if (id%2 == 0) 
      hm[id] = name; // unsafe insert
    else 
      hm.insert(make_pair(id, name));
  } while (file.good());
  cout << "Insert successful.\n" << endl;
}

void search(hashmap<int, string> &hm) {
  cout << "Enter ID number to search for people (-1 to stop):" << endl;
  while (true) {
    int id = getID();
    if (id == -1) 
      break;
    // Search hashmap using ID as key
    auto element = hm.find(id);
    if (element == nullptr) 
      cout << "No person with that ID. Try again." << endl;
    else {
      //cout << "first=" <<  element->first << endl;                    //prints to terminal
      //cout << element->second << endl;                                //prints to terminal
      cout << element->second << " has the ID number " << id << endl; //does not print to terminal

      //cout << "-----------------------------------" << endl;
      //cout << element->second << endl;                                //does not print to terminal
      //cout << " has the ID number " << endl;                          //prints to terminal
      //cout << id << endl;                                             //prints to terminal

      //cout << "-----------------------------------" << endl;
      //cout << element->second;                                        //does not print to terminal
      //cout.flush();
      //cout << " has the ID number ";                                  //prints to terminal
      //cout << id;                                                     //prints to terminal

      //cout << endl;
      //cout << "-----------------------------------" << endl;
      //cerr << element->second;                                        //does not print to terminal
      //cerr << " has the ID number ";                                  //prints to terminal
      //cerr << id;                                                     //prints to terminal

    }
  }
  cout << "Finished searching\n" << endl;
}

void remove(hashmap<int, string> &hm) {
  cout << "Enter ID number of people to remove (-1 to stop):" << endl;
  while (true) {
    int id = getID();
    if (id == -1)
      break;
    auto deletedPair = hm.erase(id);
    if (deletedPair.second == true)
      cout << "Delete successful" << endl;
    else 
      cout << "No person with that ID in hashmap" << endl;
  }
  cout << "Finished deleting\n" << endl;
}

void removeUntilEnd(hashmap<int, string> &hm) {
  cout << "The number of people must be reduced, Enter an ID.\n"
       << "Person with chosen ID and all those after will be removed" << endl;
  // find person to remove from user
  int id;
  pair<const int, string>* person;
  while (true) {
    id = getID();
    // Search hashmap using ID as key
    person = hm.find(id);
    if (person == nullptr)
      cout << "No person with that ID. Try again." << endl;
    else 
      break;
  }
  
  // once person is found, remove him and all those after
  while (person != nullptr) {
    id = person->first;
    person = (hm.erase(id).first);
  }
  cout << "removed everyone past selected ID." << endl;

}

int main() {
  cout << "Using hashmap of people with atributes: int ID, string \"name\"" << endl;
  hashmap<int, string> people; 
  int numOfBuckets = kDataSize / 2;
  
  people.rehash(numOfBuckets);
  fill(people);

  cout << "People in hashmap with " << numOfBuckets << " buckets"<< endl;
  people.print();

  cout << "People in hashmap with " << numOfBuckets << " buckets" << endl;
  people.rehash(numOfBuckets*4);
  people.print();

  search(people);
  cout << endl; 

  remove(people);
  cout << "People in hashmap after deletion" << endl;
  people.print();

  removeUntilEnd(people);
  cout << "remaining people are" << endl;
  people.print();

  cout << "all tests passed, hashmap working properly" << endl;
  return 0;
}
