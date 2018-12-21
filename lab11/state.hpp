#ifndef CS3_STATE_H_
#define CS3_STATE_H_
#include <string>
#include "process.hpp"

using std::string;

// absract state
class State {
public:
  void changeState(Process* p, State* s) {
    p->changeState(s);
  }
  virtual string report() const = 0;
  
protected:
  //State();
private:
  //virtual ~State();
};

class NewState : public State {
public:
  // Meyers Singleton
  static State* instance() {
    static State* onlyInstance = new NewState;
    return onlyInstance;
  }

  string report() const override { return "New"; }
private:
  // here and elsewhere should be stated private constructor/assignment
  // to correctly implement singleton, skipped to simplify code
  //~NewState();
  NewState() {}
};

class ReadyState : public State {
public:
  // Meyers Singleton
  static State* instance() {
    static State* onlyInstance = new ReadyState;
    return onlyInstance;
  }

  string report() const override { return "Ready"; }
private:
  // here and elsewhere should be stated private constructor/assignment
  // to correctly implement singleton, skipped to simplify code
  //~NewState();
  ReadyState() {}
};


class WaitingState : public State {
public:
  // Meyers Singleton
  static State* instance() {
    static State* onlyInstance = new WaitingState;
    return onlyInstance;
  }

  string report() const override { return "Waiting"; }
private:
  // here and elsewhere should be stated private constructor/assignment
  // to correctly implement singleton, skipped to simplify code
  //~NewState();
  WaitingState() {}
};


class TerminatedState : public State {
public:
  // Meyers Singleton
  static State* instance() {
    static State* onlyInstance = new TerminatedState;
    return onlyInstance;
  }

  string report() const override { return "Terminated"; }
private:
  // here and elsewhere should be stated private constructor/assignment
  // to correctly implement singleton, skipped to simplify code
  //~NewState();
  TerminatedState() {}
};

class RunningState : public State {
public:
  // Meyers Singleton
  static State* instance() {
    static State* onlyInstance = new RunningState;
    return onlyInstance;
  }

  string report() const override { return "Running"; }
private:
  // here and elsewhere should be stated private constructor/assignment
  // to correctly implement singleton, skipped to simplify code
  //~NewState();
  RunningState() {}
};

/*
#include <string>
#include "process.h"

using std::string;

// forward declarations
class Process;

// absract state
class State {
public:
  void changeState(Process* c, State* s) {
    c->changeState(s);
  }
protected:
  //State();
private:
  //virtual ~State();
};

class NewState : public State {
public:
  // Meyers Singleton
  static State* instance() {
    static State* onlyInstance = new NewState;
    return onlyInstance;
  }
  ~NewState();
  NewState();
private:
  // here and elsewhere should be stated private constructor/assignment
  // to correctly implement singleton, skipped to simplify code

};

class ReadyState : public State {
public:
  // Meyers Singleton
  static State* instance() {
    static State* onlyInstance = new ReadyState;
    return onlyInstance;
  }
private:
  // here and elsewhere should be stated private constructor/assignment
  // to correctly implement singleton, skipped to simplify code
  ~ReadyState();
  ReadyState();
};
*/
#endif // !CS3_STATE_H_
