#ifndef CS3_PROCESS_H_
#define CS3_PROCESS_H_

#include <string>
#include <iostream>

using std::string;

class State; // forward declaration

// context
class Process {
public:
  Process();
  // part of implementation of state pattern
  void changeState(State* s) { state_ = s; }
  string getName() const { return name_; }
  string report();
  Process* clone();
  void run(std::ostream& out = std::cout);
  bool hasFinished();
  int getRemainingRunTime();
private:
  const string name_;
  State* state_;
  static int counter;
  int remainingRunTime;
};

#endif // !CS3_PROCESS_H_

