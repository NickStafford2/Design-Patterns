#include "utilities.hpp"
#include <iostream>
#include <chrono>
#include <thread>
using std::endl;
using std::cout;

int gWaitTime = 100;

void setWaitTime(int n){
  gWaitTime = n;
}

void printBoldLineSlice(int length, std::ostream& out) {
  for (int i=0; i<length; ++i) 
    out << '#';
  out << '\n';
  out.flush();
}

void printLineSlice(int length, std::ostream& out){
  for (int i=0; i<length; ++i) 
    out << '-';
  out << '\n';
  out.flush();
}

void wait(int n) {
  // wait in milliseconds
  //for (int i = 0; i < 10; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(n));
    //std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
    //cout << ".";
  //}
//cout << endl;
}

void waitDots(int n, std::ostream& out) {
  // quick = 15 milliseconds
  for (int i = 0; i < n; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(gWaitTime));
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    //std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
    out << ".";
    out.flush();
  }
  //cout << endl;
}
