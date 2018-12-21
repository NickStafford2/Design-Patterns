#ifndef CS3_LAB_14_COMMAND
#define CS3_LAB_14_COMMAND

#include <string>
using std::string;
using std::to_string;

class Document;

// abstract command
class Command {
public:
                   Command(Document *doc) : doc_(doc) {}
  virtual          ~Command() {}
  virtual void     execute() = 0;
  virtual void     unexecute() = 0;
  virtual string   getAction() = 0;
  virtual Command* clone() = 0;
protected:
  Document*        doc_;
};

// two concrete commands
class InsertCommand : public Command {
public:
            InsertCommand(Document *doc, int line, const string &str) 
              : Command(doc), line_(line), lineText_(str) {}
  void      execute();
  void      unexecute();
  string    getAction() { return "inserted line " + to_string(line_); }
  Command*  clone();
private:
  int       line_;
  string    lineText_;
};


class EraseCommand : public Command {
public:
            EraseCommand(Document *doc, int line) 
              : Command(doc), line_(line), lineText_("") {}
  void      execute();
  void      unexecute();
  string    getAction() { return "erased line " + to_string(line_); }
  Command*  clone();
private:
  int       line_;
  string    lineText_;
};

#endif // !CS3_LAB_14_COMMAND
