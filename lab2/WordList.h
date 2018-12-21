#ifndef WORD_LIST_H_
#define WORD_LIST_H_
#include <string>
using std::string;

class WordOccurrence {
public:
  WordOccurrence(const string& word = "", int num = 0);
  bool matchWord(const string &); // returns true if word matches stored
  void increment(); // increments number of occurrences
  string getWord() const;
  int getNum() const;
  
private:
  string word_;
  int num_;
};

class WordList {
public:
  WordList(); //defult constructor
  WordList(const WordList&); //copy constructor
  ~WordList();	// destructor
  WordList& operator=(const WordList&);
  // implement comparison as friend
  friend bool equal(const WordList&, const WordList&); // elements must be sorted
  
  void addWord(const string &); // elements must be sorted
  void print(); // elements must be sorted
private:
  WordOccurrence * wordArray_; // a dynamically allocated array of WordOccurrences
  // may or may not be sorted
  int size_;
};

#endif // !WORD_LIST_H_
