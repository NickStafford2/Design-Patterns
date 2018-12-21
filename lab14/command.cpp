#include "command.hpp"
#include "document.hpp"

void InsertCommand::execute() { 
  doc_->insert(line_, lineText_);
}

void InsertCommand::unexecute() { 
  doc_->remove(line_); 
}

Command* InsertCommand::clone() {
  return new InsertCommand(doc_, line_, lineText_);
}


void EraseCommand::execute() { 
  lineText_ = doc_->remove(line_);
}

void EraseCommand::unexecute() { 
  doc_->insert(line_, lineText_);
}

Command* EraseCommand::clone() {
  return new EraseCommand(doc_, line_);
}
