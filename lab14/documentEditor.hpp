#ifndef CS3_LAB_14_TEXT_EDITOR
#define CS3_LAB_14_TEXT_EDITOR

#include <stack>
#include <string>
#include <vector>

using std::vector;
using std::string;
class Command;

// client
class DocumentEditor {
public:
         DocumentEditor(Document* d) : doc_(d), checkpoint(nullptr) {}
  bool   insert        (size_t line, string str);
  void   erase         (size_t line);
  void   undo          ();
  void   show          ();
  void   saveState     ();
  void   restoreState  ();
  string getHistory    ();
  void   redo          (const size_t);
  size_t getNumOfCommands() { return doneCommands_.size(); }
private:
  void addCommand    (Command*);
  std::stack<Command*> doneCommands_;
  Document*            doc_;
  Memento*             checkpoint;
};



#endif //! CS3_LAB_14_TEXT_EDITOR