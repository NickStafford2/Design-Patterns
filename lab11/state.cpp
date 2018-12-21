/*#include <string>
#include "process.hpp"

using std::string;

// absract state
class State {
public:
   void changeState(Process* c, State* s) {
    c->changeState(s);
  }
private:
  virtual ~State();
  State();
};

class NewState : public State {
public:
  static State* instance() {
    static State* onlyInstance = new NewState;
    return onlyInstance;
  }
private:
  // here and elsewhere should be stated private constructor/assignment
  // to correctly implement singleton, skipped to simplify code
  ~NewState();

};


class Hungry : public State {
public:
  static State* instance() {
    static State* onlyInstance = new Hungry;
    return onlyInstance;
  }
  void skipLunch(Character *c) override;
  void eat(Character *c) override;
  string report() override { return "hungry"; }
};


class Dead : public State {
public:
  static State* instance() {
    static State* onlyInstance = new Dead;
    return onlyInstance;
  }
  string report() override { return "dead"; }
};

*/