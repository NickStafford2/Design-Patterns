#include "document.hpp"
#include "memento.hpp"

void Document::insert(int line, const string &str) {
  int index = line - 1;
  if (index <= static_cast<int>(data_.size()))
    data_.insert(data_.begin() + index, str);
  else
    cout << "line out of range" << endl;
}

string Document::remove(int line) {
  int index = line - 1;
  string deletedLine = "";
  if (index < static_cast<int>(data_.size())) {
    deletedLine = data_[index];
    data_.erase(data_.begin() + index);
  }
  else
    cout << "line out of range" << endl;
  return deletedLine;
}

void Document::show() {
  for (size_t i = 0; i < data_.size(); ++i)
    cout << i + 1 << ". " << data_[i] << endl;
}

void Document::restoreState(Memento *mem) {
  *this = mem->getState();  // copying back
}

Memento* Document::createMemento() const {
  // copying the Document itself
  return new Memento(*this);
}