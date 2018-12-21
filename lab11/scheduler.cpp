#include "scheduler.hpp"
#include "utilities.hpp"
#include "process.hpp"

int Scheduler::sTimeSliceCount = 0;

Scheduler::Scheduler(std::ostream& out) : running(nullptr), 
                                          out(out),
                                          numberOfTerminatedProcesses(0) {
  prototype = new Process();
}
Scheduler::~Scheduler() {
  delete prototype;
}


void Scheduler::run() {
  // if processes still need to run, keep executing time slices
  out << "\n";
  printBoldLineSlice();
  out << "#\t\t\t\t   CPU Scheduler Activated       \t\t\t\t   #\n";
  printBoldLineSlice();
  while (!waitingQueue.empty() || !readyQueue.empty() || running != nullptr) {
    executeTimeSlice();
  }
  printBoldLineSlice();
  out << "\nAll " << numberOfTerminatedProcesses 
      << " Processes have finished executing\n" << endl;
}

void Scheduler::executeTimeSlice() {
  printLineSlice();
  out << "Time Slice: " << sTimeSliceCount++  << "      "
      << "Ready_Queue_Size=" << readyQueue.size() << "      "
      << "Waiting_Queue_Size=" << waitingQueue.size() << "      "
      << "Processes_Terminated=" << numberOfTerminatedProcesses << "\n"
      << endl;

  dispatch();
  checkForIO();

  // run the program in a try catch block to implement a trap handler
  //out << running->getName() << " is running on the CPU" << endl;
  out << running->report();
  try {
    // run may throw an exception if it needs io
    running->run();
    out << endl;
  }
  catch (const char* error) {
    // running process requires IO, send it to the waiting queue
    wait();
  }
  checkForIO();
  // running is nullptr if it moved to the waiting list
  if (running != nullptr) {
    if (running->hasFinished()) {
      exit();
    }
    else {
      // time slice has run out, switch processes
      interrupt();
    }
  }
}

void Scheduler::trapHandler() {
  out << "\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  Process* p = waitingQueue.front();
  out << "\t!! A random I/O event has occured, trap handler processing request";
  waitDots(9);
  out << endl;
    
  out << "\t!! Trap handler determined " << p->getName()
      << " is ready to run. " << endl;
  waitingQueue.pop();
  p->changeState(ReadyState::instance());
  out << "\t!! " << p->report() << endl;
  readyQueue.push(p);
  out << "\t!! Trap handler finished, resume normal execution" << endl;
  out << "\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n" << endl;
}

void Scheduler::interrupt() {
  out << "Time slice ended. Moving " << running->getName() << " to ready queue" << endl;
  running->changeState(ReadyState::instance());
  out << running->report() << endl;
  readyQueue.push(running);
  //delete running;
  running = nullptr;
}

void Scheduler::admit() {//Process* newProcess) {
  Process* newProcess = prototype->clone();
  out << newProcess->report() ;
  out << " - Requires " << newProcess->getRemainingRunTime() << "ms to execute." << endl;
  out << newProcess->getName() << " created, changing state and moving to ready queue";
  //waitDots(3);
  out << endl;
  newProcess->changeState(ReadyState::instance());
  out << newProcess->report() << endl;
  //int n = newProcess->getRemainingRunTime();
  //bool b = newProcess->hasFinished();
  readyQueue.push(newProcess);
}
// REQUIRES: ready == nullptr
// ENSURES: a process is dispacthed to the CPU
void Scheduler::dispatch() {
  if (readyQueue.empty()) {
    busyWait();
  }
  // busy wait ends only if a process has been moved to the ready queue
  out << "Dispatching next process to CPU: \n";
  running = readyQueue.front();
  readyQueue.pop();
  running->changeState(RunningState::instance());
  //out << running->report() << endl;
}

void Scheduler::exit() {
  running->changeState(TerminatedState::instance());
  out << running->report() << endl;
  delete running;
  running = nullptr;
  ++numberOfTerminatedProcesses;
}
void Scheduler::wait() {
  out << "\n" << running->getName() 
      << " requires I/O, sending to the waiting queue" << endl;
  running->changeState(WaitingState::instance());
  out << running->report() << endl;
  waitingQueue.push(running);
  running = nullptr;
  //run();
}

void Scheduler::busyWait() {
  out << "No processes are ready, waiting for I/O";
  while (true) {
    waitDots(3);
    if (checkForIO()){
      break;
    }
  }
}

bool Scheduler::checkForIO() {
  // io events occur randomly by user input. if io occurs, invoke trap handler
  if (rand() % 8 == 0) {
    if (!waitingQueue.empty()) {
      out << endl;
      trapHandler();
      return true;
    }
    else 
      return false;
  } 
  else
    return false;
}
