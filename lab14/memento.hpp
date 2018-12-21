#ifndef CS3_LAB_14_MEMENTO
#define CS3_LAB_14_MEMENTO

#include "document.hpp"

class Memento {
public:
                  Memento(const Document& doc) : doc_(doc) {}
  const Document& getState() const { return doc_; }
private:
  const Document  doc_;
};


#endif // !CS3_LAB_14_MEMENTO
