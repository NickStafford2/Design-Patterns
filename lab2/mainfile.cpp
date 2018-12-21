/*	Name: Nicholas Stafford
	Program:    WordList
	Class:      cs44001
	Due Date:   2/1/18

Description: read a text file, count how often each word occurs in the
file and outputs the words, and how often they appear in the file
words are alphanumeric. ignore punctuation and whitespace. case insensitive
hello and Hello are the same word.
*/

#include "WordList.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::ifstream;

const int maxWordLength = 50;

int main(int argc, char *argv[]) {
  
  if (argc != 2) {
    cerr << "invalid number of arguments" << endl;
    return 1;
  }
  string inputFile = argv[1];
  
  ifstream ifs(inputFile);
  
  if (ifs.fail()) {  // Ensure file is open
    cerr << "failed to open file" << endl;
    return 1;
  }
  WordList list1;
  
  string word;
  while (ifs >> word) { // reads and returns next word 		
    string fixedWord;
    for (int i = 0; i < word.size(); ++i) {
      char tempChar = word[i];
      /* char must be unsigned for cctype functions to work properly. 
	 only accept chars in the ascII */
      if (0 <= tempChar && tempChar <= 127) {
	/* if tempchar is alphanumeric convert to lowercase, 
	   and append to fixedword*/
	if (isalnum(tempChar)) {
	  // change uppercase to lowercase
	  if (isupper(tempChar)) tempChar = char(tolower(tempChar));
	  fixedWord.append(sizeof(tempChar), tempChar);
	}
      }
      // if tempc is not alphanumeric ignore it
    }
    list1.addWord(fixedWord);
  }
  list1.print();
  ifs.close();
}
