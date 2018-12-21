#ifndef NS_IO_CONTROL_HPP_
#define NS_IO_CONTROL_HPP_

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::istream;
using std::ostream;
using std::string;

namespace nsio {

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
    SpacerWrap(int maxlength, string str);
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
/*
static void ltrim(string&);
static void rtrim(string&);
static void trim(string&);
static std::string ltrim_copy(string);
static std::string rtrim_copy(string);
static  std::string trim_copy(string);
*/

#endif // NS_IO_CONTROL_HPP_
