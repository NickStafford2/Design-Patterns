#ifndef CS3_UTILITIES_HPP_
#define CS3_UTILITIES_HPP_
#include <iostream>

void printBoldLineSlice(int length = 100, std::ostream& out = std::cout);
void printLineSlice(int length = 100, std::ostream& out = std::cout);

void setWaitTime(int);
void wait(int n);
void waitDots(int n=1, std::ostream& out = std::cout);


#endif //!CS3_UTILITIES_HPP_
