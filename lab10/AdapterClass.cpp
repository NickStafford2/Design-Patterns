// figures: class adapter pattern
// Mikhail Nesterenko
// 2/16/2014
#include "nsio.hpp" // my custom io file
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using nsio::getChar;
using nsio::getInt;

// base interface
class Figure {
public:
  virtual void draw() = 0;
  virtual ~Figure() {}
};

// adaptee/implementer
class LegacyRectangle {
public:
  LegacyRectangle(int topLeftX, int topLeftY, 
                  int bottomRightX, int bottomRightY) :
                  topLeftX_(topLeftX), topLeftY_(topLeftY), 
                  bottomRightX_(bottomRightX), bottomRightY_(bottomRightY) {}

  int getTopLeftX() { return topLeftX_; }
  int getTopLeftY() { return topLeftY_; }
  int getBottomRightX() { return bottomRightX_; }
  int getBottomRightY() { return bottomRightY_; }

  void setTopLeftX(int x) { topLeftX_ = x ; }
  void setTopLeftY(int y) {  topLeftY_ = y; }
  void setBottomRightX(int x) { bottomRightX_ = x; }
  void setBottomRightY(int y) { bottomRightY_ = y; }

  void oldDraw() {
    for (int i = 0; i < bottomRightY_; ++i) {
      for (int j = 0; j < bottomRightX_; ++j)
        if (i >= topLeftY_  && j >= topLeftX_)
          cout << '*';
        else
          cout << ' ';
      cout << endl;
    }
  }
private: // defining top/left and bottom/right coordinates 
  int topLeftX_;
  int topLeftY_;
  int bottomRightX_;
  int bottomRightY_;
};

// adapter uses multiple inheritance to inherit
// interface and implementation
class SquareAdapter : public Figure,
                      private LegacyRectangle {
public:
  SquareAdapter(int size) : LegacyRectangle(0, 0, size, size), size_(size){};
  void draw() override {
    oldDraw();
  }
  int size() {
    //returns the current square size
    return size_;
  }
  void resize(int newSize) {
    // code from whiteboard
    //move(0, 0, newSize, newSize);
    size_ = newSize;
    setBottomRightX(size_);
    setBottomRightY(size_);
  }
private: 
  int size_;
};
///////////////////////////////////////////////////////////////////////////////
/*
Demonstrate this functionality by coding main() as follows: 
    - ask the user for the size of a square, 
    - declare a square of the user-specified size, 
    - draw the square; 
    - then ask the user for a new size, 
    - resize the square to the new size 
    - redraw it.
*/

int main() {
  int size = getInt("Enter a size for a square: ");
  cout << endl;

  SquareAdapter* square = new SquareAdapter(size);
  square->draw();

  size = getInt("\nEnter a new size: ");

  //reinterpret_cast <SquareAdapter>(square);
  square->resize(size);
  square->draw();
  int i = 0;
}