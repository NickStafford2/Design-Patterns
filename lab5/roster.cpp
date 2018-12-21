/* Author:    Nicholas Stafford
                    - based on code from Mikhail Nesterenko 3/11/2014
   Program:    roster.cpp
   Class:      cs44001
   Due Date:   2/15/18

   Description: Displays a list of students and the classes they are enrolled in.
   the same student will be in multiple classes
   assume all students have different names

   Arguments: Takes files as arguments when executable is called
   each input file name is the name of the class (.txt extension permitted)
   each input file contains student names ordered like so:
       firstname1 lastname1
       firstname2 lastname2
       firstname3 lastname3
       ...

   Does NOT take dropouts.txt. dropout is not implemented.
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstdlib>
#include <list>
#include <utility>

using std::ifstream;
using std::string;
using std::getline;
using std::map;
using std::list;
using std::cout;
using std::endl;
using std::move;
using std::make_pair;

// reading a list from a fileName
void readRoster(list<string>& roster, string fileName);

// printing a list out
void printStudents(const map<string, list<string>>& studentEntries_);


int main(int argc, char* argv[]) {
  
  if (argc <= 1) {
    cout << "usage: " << argv[0]
	 << " list of courses" << endl; exit(1);
  }
  
  /*	studentEntries is a map of lists of strings
	the key to map is the students first and last name
	the list is a list of all the classes the student is taking
  */
  map<string, list<string>> studentEntries;

  // search through each class file for students
  for (int i = 1; i < argc; ++i) { // start at one to avoid argv[0] 
    
    // create a roster of all students in the class
    list<string> classRoster;
    readRoster(classRoster, argv[i]);
    
    string className = argv[i];
    
    // if classname file ends in ".txt" remove this from the class name
    if (className.substr(className.size() - 4) == ".txt")
      className.erase(className.size() - 4); // erase last 4 characters. 
    
    // for each student in the class
    for (const string studentName_ : classRoster) {
      
      //check if studentEntries contains that student
      auto it = studentEntries.find(studentName_);
      
      // if student already exists add class to map
      if (it != studentEntries.end())
	it->second.push_back(className);
      
      // if student is not already in studentEntries add new list
      else studentEntries[studentName_].push_back(className);
    }
  }
  
  printStudents(studentEntries);
  cout << endl;
}

void readRoster(list<string>& roster, string fileName) {
  //   ifstream course(fileName.c_str());
  ifstream course(fileName); // I am trying it
  
  string first, last;
  while (course >> first >> last)
    // add new string to list
    roster.push_back(first + ' ' + last);
  course.close();
}

// printing a list of lists out
void printStudents(const map<string, list<string>>& studentEntries_) {
  // for neatness create a spacer so classes start at the same location
  size_t mostDigits = 0;
  for (auto it = studentEntries_.cbegin(); it != studentEntries_.end(); ++it) {
    if (it->first.size() > mostDigits)
      mostDigits = it->first.size();
  }
  
  cout << "first name, last name:  courses " << endl;
  for (auto it = studentEntries_.cbegin(); it != studentEntries_.end(); ++it) {
    string spaceString(mostDigits - (it->first).size(), ' ');
    
    cout << it->first + ':' + spaceString;
    for (auto s : it->second)
      cout << s << ' ';
    cout << endl;
  }
}
