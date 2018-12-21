#ifndef CS3_LAB_14_DOCUMENT
#define CS3_LAB_14_DOCUMENT

//#include "memento.hpp"

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;

class Memento;

// receiver
class Document {
public:
                  Document      (const vector<string>& data = {}) 
                                  : data_(data) {}
  void            insert        (int line, const string &str);
  string          remove        (int line);
  void            show          ();
  Memento*        createMemento ()          const;
  void            restoreState  (Memento*);
  size_t          getLineCount  () { return data_.size(); }
private:
  vector<string>  data_;
};

#endif // !CS3_LAB_14_DOCUMENT
