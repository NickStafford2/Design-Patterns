#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iostream>

using std::string;
using std::ofstream;


class logger {
  // implimented as a singleton
public:
  static logger* instance(); 
  void report(const string&);
  ~logger();

private:
  logger();
  ofstream fout;
  logger(const logger&) = delete;
  logger& operator=(const logger&) = delete;
};

logger::logger() {
  // open file
  fout.open("log.txt", std::fstream::out | std::fstream::app);
}

logger::~logger() {
  // close file
  report("logger destructor called");
  fout.flush();
  fout.close();
  //cout << "logger destructor called" << endl;
}

logger* logger::instance() {
  static logger log;
  return &log;
}

void logger::report(const string& message) {
  std::stringstream output;

  struct tm newtime;
  time_t now = time(0);
  localtime_r(&newtime, &now);
  //localtime_s(&newtime, &now);
  const int bufferSize = 1024;
  char buffer[bufferSize];
  strftime(buffer, bufferSize, "%a, %d.%m.%Y %H:%M:%S", &newtime); //const struct tm* timeptr

  output << buffer << " - " << message << "\n";
  fout << output.str();
  fout.flush();
}

int fibbonacci(int n, int nextNum = 0, int nextNextNum = 1) {

  logger::instance()->report("fibbonacci recursive");
  if (n == 0) return nextNum;
  if (n == 1) return nextNextNum;
  return fibbonacci(n - 1, nextNextNum, nextNum + nextNextNum);
}

string getSecretString() {
  logger::instance()->report("secret string called");
  return "a day without sunshine is, you know, night.";
}


int main() {
  logger::instance()->report("Main Called");
  logger::instance()->report("calling fibbonacci(2)");
  fibbonacci(2);
  logger::instance()->report("back to main");
  
  logger::instance()->report("calling secretString");
  getSecretString();
  logger::instance()->report("leaving main");
  return 0;
}
