#ifndef CS3_SCHEDULER_H_
#define CS3_SCHEDULER_H_
#include <iostream>
#include "state.hpp"
#include "process.hpp"
#include <queue>

using std::cout;
using std::cin;
using std::endl;
using std::queue;

// prototype client
class Scheduler {
public: 
  Scheduler(std::ostream& out = cout);
  ~Scheduler();

  void run();
  void admit();// (Process* newProcess);
  static const int ksTimeSlice = 300;
private:
  void interrupt();
  void exit();
  void displayQueue();
  bool checkForIO();
  void executeTimeSlice();
  void dispatch();
  void wait();
  void trapHandler();
  void busyWait();
  // uses first in first out scheduling
  queue<Process*> readyQueue;
  queue<Process*> waitingQueue;
  Process* running;
  Process* prototype;
  std::ostream& out;
  static int sTimeSliceCount;
  int numberOfTerminatedProcesses;
};

#endif //!CS3_SCHEDULER_H_