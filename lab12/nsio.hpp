#ifndef NS_IO_CONTROL_HPP_
#define NS_IO_CONTROL_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <array>

using std::cout;
using std::cin;
using std::endl;
using std::istream;
using std::ostream;
using std::string;
using std::vector;
using std::array;

namespace nsio {

//////////////////////////////////////////////////////////////////////////
  // use like normal function ONLY IN DEBUGGING
  #define dprint(variable) std::cout <<#variable"="<<(variable) << "\n"

  void printBoldLineSlice(int length = 100, std::ostream& out = std::cout);
  void printLineSlice(int length = 100, std::ostream& out = std::cout);

  void print(ostream& out = cout);
  //void print(const char* chars, ostream& out=cout);
  //void print(char c, ostream& out=cout);
  //void print(int n, ostream& out=cout);
  void print(string name, string value, ostream& out = cout);
  void print(int argc, char* argv[], ostream& out = cout);
  
  template<typename T>
  void print(T toPrint, ostream& out=cout){
    out << toPrint;
  }

  template<typename T, typename U>
  void print(T toPrint, U toPrint2, ostream& out=cout){
    out << toPrint << toPrint2;
  }

  // Print out all values of a vector of any type
  template<typename T> 
  void print(const string& name, const vector<T>& vec, ostream& out = cout) {
    for (int i=0; i<vec.size(); ++i) {
      out << "  " << name << "[" << i << "]=" << vec[i];
    }
  }

  // Print out all values of array of any size and type
  template<typename T, std::size_t SIZE> 
  void print(const string& name, const array<T, SIZE>& arr, ostream& out = cout) {
    for (int i=0; i<SIZE; ++i) {
      out << "  " << name << "[" << i << "]=" << arr[i];
    }
  }

  void println(ostream& out = cout);
  //void println(const char* chars, ostream& out=cout);
  //void println(char c, ostream& out=cout);
  void println(string name, string value, ostream& out = cout);
  void printMain(int argc, char* argv[], ostream& out = cout);
  template<typename T>
  void println(T toPrint, ostream& out=cout){
    out << toPrint << endl;
  }

  template<typename T, typename U>
  void println(T toPrint, U toPrint2, ostream& out=cout){
    out << toPrint << toPrint2 << endl;
  }

  // Print out all values of a vector of any type
  template<typename T> 
  void println(const string& name, const vector<T>& vec, ostream& out = cout) {
    for (int i=0; i<vec.size(); ++i) {
      out << "  " << name << "[" << i << "]=" << vec[i] << endl;
    }
  }

  // Print out all values of array of any size and type
  template<typename T, std::size_t SIZE> 
  void println(const string& name, const array<T, SIZE>& arr, ostream& out = cout) {
    for (int i=0; i<SIZE; ++i) {
      out << "  " << name << "[" << i << "]=" << arr[i] << endl;
    }
  }

//////////////////////////////////////////////////////////////////////////

  void clearCin(istream& in = cin);

  int getInt(const string& message = "Enter an int: ", 
             const string& error = "invalid, try again: ",
            istream& in = cin,
            ostream& out = cout);

  double getDouble(const string& message = "Enter an double: ", 
                   const string& error = "invalid, try again: ",
                   istream& in = cin,
                   ostream& out = cout);

  char getChar(const string& message = "Enter an char: ", 
               const string& error = "invalid, try again: ",
               istream& in = cin,
               ostream& out = cout);


  inline string quote(string str) {
    return "\"" + str + "\"";
  }

  class Spacer {
  public:
    Spacer(int size = 0, char c = ' ');
    Spacer(const Spacer&); //Copy Constructor

    Spacer& operator=(Spacer); //Assignment Copy

    int length() const;  //Actual number of chars in string
    string toStr();
    friend std::ostream& operator<<(std::ostream&, const Spacer&);
  private:
    string str;
    char c;
  };

  class SpacerWrap {
  public:
    SpacerWrap(int maxlength, string str, char spacer=0);
    SpacerWrap(const SpacerWrap&); //Copy Constructor

    SpacerWrap& operator=(SpacerWrap); //Assignment Copy

    int length() const;  //Actual number of chars in string and spacer
    string toStr();

    friend std::ostream& operator<<(std::ostream&, const SpacerWrap&);
  private:
    string str;
    Spacer spaces;
  };
}

void setWaitTime(int);
void wait(int n);
void waitDots(int n=1, std::ostream& out = std::cout);


/*
static void ltrim(string&);
static void rtrim(string&);
static void trim(string&);
static std::string ltrim_copy(string);
static std::string rtrim_copy(string);
static  std::string trim_copy(string);
*/

#endif // NS_IO_CONTROL_HPP_
