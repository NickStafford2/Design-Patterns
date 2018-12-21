/* 
  Author:       Nicholas Stafford
  Project:      Nick Stafford Input Output common solutions
  Description:  My personal list of functions I commonly use across projects 
                to code more effectivly. Mostly this is I/O, but other
                functions and classes exist here as well

*/
#include "nsio.hpp"

#include <iostream>
#include <chrono>
#include <thread>
//#include <algorithm> 
//#include <cctype>
//#include <locale>

namespace nsio{

//////////////////////////////////////////////////////////////////////////
  void printBoldLineSlice(int length, std::ostream& out) {
    for (int i=0; i<length; ++i) 
      out << '#';
    out << '\n';
    out.flush();
  }

  void printLineSlice(int length, std::ostream& out) {
    for (int i=0; i<length; ++i) 
      out << '-';
    out << '\n';
    out.flush();
  }

  // output empty line
  void println(ostream& out) {
    out << endl;
  }
  // output chars line
  void println(const char* chars, std::ostream& out) {
    out << chars << endl;
  }
  // output char line
  void println(char c, std::ostream& out) {
    out << c << endl;
  }  
  /*
  // output int line
  void print(int n, std::ostream& out) {
    out << c << endl;
  }
  */
  // output name and value neatly
  void println(string name, string value, ostream& out) {
    out << name << "=" << value << endl;
  }
  void printMain(int argc, char* argv[], ostream& out){
    for (int i=0; i<argc; ++i) 
      out << "argv[" << i << "]=" << argv[i] << endl;
  }
  



  /*
  // output int line
  void print(int n, std::ostream& out) {
    out << c << endl;
  }
  */
  // output name and value neatly
  void print(string name, string value, ostream& out) {
    out << name << "=" << value;
  }
//////////////////////////////////////////////////////////////////////////


  void clearCin(istream& in){
    // used to clear the cin stream
    // remove any possible error flags
    cin.clear();
    // if user entered in lots of whitespace, ignore it
    cin.ignore(10000, '\n'); 
  }


  // get an int from the user. never give up or stop asking.
  int getInt(const string& message, 
             const string& error, 
             istream& in,
             ostream& out) {
    out << message;
    int n;
    string input;
    while (true) {
      in >> input;

      try {
        n = std::stoi(input);
        clearCin();
        break;
      }
      catch (const std::exception&) {
        out << error;
        clearCin();
      }
    }
    return n;
  }

  double getDouble(const string& message, 
                const string& error, 
                istream& in,
                ostream& out) {
    out << message;
    double n;
    string input;
    while (true) {
      in >> input;

      try {
        n = std::stod(input);
        clearCin();
        break;
      }
      catch (const std::exception&) {
        out << error;
        clearCin();
      }
    }
    return n;
  }

  char getChar(const string& message, 
                 const string& error, 
                 istream& in,
                 ostream& out) {
    out << message;
    char c;
    while (true) {
      in >> c;

      try {
        if (c < 33 || c > 126) throw "invalid char";
        clearCin();
        break;
      }
      catch (const std::exception&) {
        out << error;
        clearCin();
      }
      catch (const char* ) {
        clearCin();
      }
    }
    return c;
  }


  ///////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////

  Spacer::Spacer(int size, char c) : c(c) {
    for (int i = 0; i < size; ++i)
      str += c;
  }

  Spacer::Spacer(const Spacer & rhs) : c(rhs.c) {
    str = rhs.str;
  }

  Spacer& Spacer::operator=(Spacer rhs) {
    str = rhs.str;
    c = rhs.c;
    return *this;
  }

  string Spacer::toStr() {
    return str;
  }

  inline int Spacer::length() const {
    return str.length();
  }

  std::ostream & operator<<(std::ostream & out, const Spacer & rhs) {
    out << rhs.str;
    return out;
  }

  ///////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////


  SpacerWrap::SpacerWrap(int maxlength, string str, char fillChar) {
    int spaceSize = maxlength - str.length();
    this->str = str;
    spaces = Spacer(spaceSize, fillChar);
  }

  string SpacerWrap::toStr() {
    string s;
    s += str;
    s += spaces.toStr();
    return s;
  }

  SpacerWrap::SpacerWrap(const SpacerWrap& rhs) {
    str = rhs.str;
    spaces = rhs.spaces;
  }

  SpacerWrap & SpacerWrap::operator=(SpacerWrap rhs) {
    str = rhs.str;
    spaces = rhs.spaces;
    return *this;
  }

  inline int SpacerWrap::length() const {
    return str.length() + spaces.length();
  }

  std::ostream & operator<<(std::ostream & out, const SpacerWrap & rhs) {
    out << rhs.str;
    out << rhs.spaces;
    return out;
  }

  ///////////////////////////////////////////////////////////////////////////////
  ///////////////////Wait Functions//////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////

  int gWaitTime = 100;

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

  void setWaitTime(int n){
    // in milliseconds
    gWaitTime = n;
  }

  ///////////////////////////////////////////////////////////////////////////////
  ///////////////////Free Functions////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////

  ///////////////////Trim Strings////////////////////////////////////////////////
  /*
  // trim from start (in place)
  static inline void ltrim(string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
      return !std::isspace(ch);
    }));
  }

  // trim from end (in place)
  static inline void rtrim(string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
      return !std::isspace(ch);
    }).base(), s.end());
  }

  // trim from both ends (in place)
  static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
  }

  // trim from start (copying)
  static inline std::string ltrim_copy(string s) {
    ltrim(s);
    return s;
  }

  // trim from end (copying)
  static inline std::string rtrim_copy(string s) {
    rtrim(s);
    return s;
  }

  // trim from both ends (copying)
  static inline std::string trim_copy(string s) {
    trim(s);
    return s;
  }
  */
}