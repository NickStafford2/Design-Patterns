#include "document.hpp"
#include "documentEditor.hpp"
#include "command.hpp"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::to_string;

bool DocumentEditor::insert(size_t line, string str) {
  if (line > doc_->getLineCount()) {
    cout << "line " << line << " does not exist in document" << endl;
    return false;
  }
  addCommand(new InsertCommand(doc_, line, str));
  return true;
}

void DocumentEditor::erase(size_t line) {
  addCommand(new EraseCommand(doc_, line));
}

void DocumentEditor::undo() {
  if (doneCommands_.size() != 0) {
    Command *com = doneCommands_.top();
    doneCommands_.pop();
    com->unexecute();
    delete com; // don't forget to delete command
  }
  else
    cout << "no commands to undo" << endl;
}

void DocumentEditor::show() {
  doc_->show(); 
}

void DocumentEditor::saveState() {
  checkpoint = doc_->createMemento();
}

void DocumentEditor::restoreState() {
  if (checkpoint) {
    doc_->restoreState(checkpoint);
    // flush the command stack
    while (!doneCommands_.empty())
      doneCommands_.pop();
  }
  else
    cout << "state has not been saved" << endl;
}

void DocumentEditor::addCommand(Command* com) {
  com->execute();
  doneCommands_.push(com);
}


void DocumentEditor::redo(const size_t commandNumber) {
  if (commandNumber > doneCommands_.size()) {
    cout << "invalid command" << endl;
  }
  int commandCounter = 0;
  std::stack<Command*> cmdCopy(doneCommands_);
  while (!cmdCopy.empty()) {
    //Command* topCommand = cmdCopy.top();
    if (commandCounter++ == commandNumber) {
      addCommand(cmdCopy.top()->clone());
      break;
    }
    cmdCopy.pop();
  }
}

string DocumentEditor::getHistory() {
  string returnString = "";
  int commandCounter = 0;
  std::stack<Command*> cmdCopy(doneCommands_);
  while (!cmdCopy.empty()) {
    //Command* topCommand = cmdCopy.top();
    returnString += to_string(commandCounter++) + ". ";
    returnString += cmdCopy.top()->getAction() + "\n";
    cmdCopy.pop();
  }
  return returnString;
}

