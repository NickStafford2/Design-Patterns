// Nicholas Stafford
// lab 10
// filled/hollow/enhanced figures demonstrates Bridge Design Pattern,
// square is either hollow or square and is painted with a particular character,
// it is bridged over Figure --> Fill abstract body/handle
// 

#include "nsio.hpp" // my custom io file

#include <iostream>

using std::cout; 
using std::endl; 
using std::cin;
using nsio::getChar;
using nsio::getInt;

// abstract body
class Fill {
public:
  Fill(char fillChar, char borderChar) :fillChar_(fillChar), 
                                        borderChar_(borderChar) {}
  virtual char getBorderChar() = 0;
  virtual char getFillChar() = 0;
  virtual ~Fill() {}
protected:
  char fillChar_;
  char borderChar_;
};

// concrete body
class Hollow : public Fill {
public:
  Hollow(char borderChar) :Fill(' ', borderChar) {}
  char getBorderChar() override { return borderChar_; }
  char getFillChar() override { return fillChar_; }
  ~Hollow() {}
};

// another concrete body
class Filled : public Fill {
public:
  Filled(char fillChar) :Fill(fillChar, fillChar) {}
  char getBorderChar() override { return borderChar_; }
  char getFillChar() override { return fillChar_; }
  ~Filled() {}
};

///////////////////////////////////////////////////////////////////////////////
// Create another derived paint class EnhancedFilled that inherits from Filled 
// but initializes both paint characters to two different values.Demonstrate 
// the operation of all three paint classes by drawing three differently 
// painted squares.

// another concrete body
class EnhancedFilled : public Fill {
public:
  EnhancedFilled(char fillChar, char borderChar) :Fill(fillChar, borderChar) {}
  char getBorderChar() override { return borderChar_; }
  char getFillChar() override { return fillChar_; }
  ~EnhancedFilled() {}
};




/*
///////////////////////////////////////////////////////////////////////////////
In class Figure, implement a function changeFill(cont Fill*);
-That changes the fill of a figure.
- Demonstrate the operation of your code by printing the same figure in one
fill and then in another.
*/
// abstract handle
class Figure {
public:
  Figure(int size, Fill* fill) : size_(size),
    fill_(fill) {}
  virtual void draw() = 0;
  virtual ~Figure() {}
  void changeFill(const Fill* x) {
    // changes the fill of a figure.
    fill_ = const_cast<Fill*>(x);
  }
protected:
  int size_;
  Fill *fill_;
};

// concrete handle
class Square : public Figure {
public:
  Square(int size, Fill* fill) : Figure(size, fill) {}
  void draw() override;
};


void Square::draw() {
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j)
      if (i == 0 || j == 0 || i == size_ - 1 || j == size_ - 1)
        cout << fill_->getBorderChar();
      else
        cout << fill_->getFillChar();
    cout << endl;
  }
}


int main() {
  //cout << "demonstrating changeFill" << endl;

  //char fillChar, borderChar;
  //int size;
  char fillChar =   getChar("Enter fill character: ");
  char borderChar = getChar("Enter border character: ");
  int size =        getInt("Enter size: ");
  //cout << "Enter fill character: ";
  //cin >> fillChar;
  /*cout << "Enter border character: ";
  cin >> borderChar;
  cout << "Enter size: ";
  cin >> size;
*/
  Figure *hollowBox   = new Square(size, new Hollow(borderChar));
  Figure *filledBox   = new Square(size, new Filled(fillChar));
  Figure *enhancedBox = new Square(size, new EnhancedFilled(fillChar, borderChar));

  cout << "generating 3 boxes from user input: " << endl;
  cout << "\nHollow Box: " << endl;
  hollowBox->draw();
  cout << "\nFilled Box: " << endl;
  filledBox->draw();
  cout << "\nEnhanced Box: " << endl;
  enhancedBox->draw();

  cout << "\n\nDemonstrating changeFill on the following square" << endl;

  borderChar = '#';
  fillChar = '?';
  Figure *changingBox = new Square(8, new EnhancedFilled(fillChar, borderChar));
  changingBox->draw();
  char nextFillChar = getChar(
    "\nwhat type of box do you wish to change this into? (h/f) ");
  //cout << "\nwhat type of box do you wish to change this into? (h/f) " << endl;
  //char nextFillChar;
  //cin >> nextFillChar;
  Fill *nextFill; 
  if (nextFillChar == 'h')
    nextFill = new Hollow(borderChar);
  else if (nextFillChar == 'f')
    nextFill = new Filled(borderChar);
  else {
    std::cerr << "invalid input" << endl;
    exit(1);
  }

  changingBox->changeFill(nextFill);
  int i = 0;

  cout << "\nfill of box has been changed:" << endl;
  changingBox->draw();
}

/*
///////////////////////////////////////////////////////////////////////////////
In class Figure, implement a function changeFill(cont Fill*); 
    - That changes the fill of a figure. 
    - Demonstrate the operation of your code by printing the same figure in one 
      fill and then in another.

///////////////////////////////////////////////////////////////////////////////
Make it so that the border and the inside of the figure can be painted with two
different characters. Specifically, base class Fill should contain two
characters: 
    - one for border paint
    - one for internal paint. 
The constructor for this class should now accept two characters to be assigned 
to the two member variables. 

The derived class Hollow should initialize the border paint to a character, and 
the internal paint character to a space. 

The derived class Filled should initialize both paints to the same character.

///////////////////////////////////////////////////////////////////////////////
Create another derived paint class EnhancedFilled that inherits from Filled but
initializes both paint characters to two different values. Demonstrate the
operation of all three paint classes by drawing three differently painted
squares.
///////////////////////////////////////////////////////////////////////////////
*/
  /*Fill* hollowPaintY = new Hollow('Y');
  Fill* filledPaintStar = new Filled('*');

  Figure *smallBox = new Square(4, filledPaintStar);
  Figure *bigBox = new Square(10, hollowPaintY);

  smallBox->draw();
  cout << endl;
  bigBox -> draw();
  cout << endl;

  // ask user for figure parameters
  cout << "Enter fill character: ";
  char fchar, ifFilled;
  cin >> fchar;
  cout << "Filled or hollow? [f/h] ";
  cin >> ifFilled;
  cout << "Enter size: "; 
  int size; 
  cin >> size;

  Figure *userBox = new Square(size, ifFilled == 'f'?
                                     static_cast<Fill *>(new Filled(fchar)):
                                     static_cast<Fill *>(new Hollow(fchar)));

  Figure *userBox = ifFilled == 'f' ?
                    new Square(size, new Filled(fchar)) :
                    new Square(size, new Hollow(fchar));
  
  userBox->draw();
  cout << endl;
  */
//}
