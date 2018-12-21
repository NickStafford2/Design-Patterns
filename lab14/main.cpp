#include "document.hpp"
#include "memento.hpp"
#include "command.hpp"
#include "documentEditor.hpp"

#include <vector>
#include <string>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void insertOption(DocumentEditor& editor) {
  size_t line;
  string str;
  cout << "line number to insert: ";
  cin >> line;
  cout << "line to insert: ";
  cin.get();
  getline(cin, str);
  editor.insert(line, str);
}

void eraseOption(DocumentEditor& editor) {
  size_t line;
  cout << "line number to remove: ";
  cin >> line;
  editor.erase(line);
}

void redoOption(DocumentEditor& editor) {
  if (editor.getNumOfCommands() == 0) {
    cout << "can not redo, no commands in history" << endl;
  }
  else {
    size_t line;
    cout << editor.getHistory() << endl;
    cout << "What command would you like to redo? ";
    cin >> line;
    editor.redo(line);
  }
}

int main() {
  string hLine;
  hLine += "-----------------------------------------------------------";
  hLine += "-----------------------------------------------------------";

  const vector<string> lorem = 
    {
      "Lorem Ipsum is simply dummy text of the printing and typesetting",
      "industry. Lorem Ipsum has been the industry's standard dummy text",
      "ever since the 1500s, when an unknown printer took a galley of",
      "type and scrambled it to make a type specimen book. It has",
      "survived five centuries." 
    };
  Document       doc(lorem);
  DocumentEditor editor(&doc);
  char           option;

  do {
    cout << hLine << endl;
    doc.show();
    cout << endl;

    cout << "Enter option: "
         << "(i)nsert line, "
         << "(e)rase line, "
         << "(u)ndo last command, "
         << "(c)heckpoint, "
         << "roll (b)ack: "
         << "(h)istory, "
         << "(r)edo command ";
    cin  >> option;

    switch (option) {
    case 'i':  insertOption(editor);                  break;
    case 'e':  eraseOption(editor);                   break;
    case 'u':  editor.undo();                         break;
    case 'c':  editor.saveState();                    break;
    case 'b':  editor.restoreState();                 break;
    case 'h':  cout << editor.getHistory() << endl;   break;
    case 'r':  redoOption(editor);                    break;
    }
  } while (option == 'i' || 
           option == 'e' ||
           option == 'u' || 
           option == 'c' ||
           option == 'b' ||
           option == 'h' ||
           option == 'r' );
  cout << hLine << endl;
    
  int i = 0;
}