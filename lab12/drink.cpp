// Nicholas Stafford
// lab 12
// cs3
/*
//#include "drink.hpp"
#include "nsio.hpp" // my personal repository for easy input and output
#include <iostream>
#include <ctype.h> // for tolower()
#include <string>
#include <sstream>      // std::istringstream

//#include <vector>

using std::cout;
using std::endl;
using std::cin;
using nsio::getChar;
using nsio::print;
using nsio::println;
using std::string;
//using std::vector;


enum class DrinkType { small, medium, large };

class Drink {
public:
  Drink(DrinkType type = DrinkType::medium) : type_(type) {
    if      (type_ == DrinkType::small)   size_= "small";
    else if (type_ == DrinkType::medium)  size_= "medium";
    else                                  size_= "large";


  }
  virtual double getPrice() const {
    if      (type_ == DrinkType::small)   return ksSmallPrice_;
    else if (type_ == DrinkType::medium)  return ksMediumPrice_;
    else                                  return ksLargePrice_;
  }
  virtual string getName() const {return "";}
  virtual string getSize() const {return size_;}
  //void   setName(string name) {name_ = name;}
private: 
  DrinkType type_;
  string size_;
  constexpr static double ksLargePrice_  = 3.00;
  constexpr static double ksMediumPrice_ = 2.00;
  constexpr static double ksSmallPrice_  = 1.00;
};

class SprinkledDrink: public Drink {
public:
  SprinkledDrink(const Drink* wrapped): wrapped_(wrapped) {}
  double getPrice() const override {return 0.50 + wrapped_->getPrice();} 
  string getName() const override {return "Sprinkles " + wrapped_->getName();}
private:
  const Drink *wrapped_;
};


class CaramelDrink: public Drink {
public:
  CaramelDrink(const Drink* wrapped): wrapped_(wrapped) {}
  double getPrice() const override { return 0.20 + wrapped_->getPrice();} 
  string getName() const override {return "Caramel " + wrapped_->getName();}
private:
  const Drink *wrapped_;
};

class MilkFoamDrink: public Drink {
public:
  MilkFoamDrink(const Drink* wrapped): wrapped_(wrapped) {}
  double getPrice() const override { return 0.40 + wrapped_->getPrice();} 
  string getName() const override {return "Foam " + wrapped_->getName();}
private:
  const Drink *wrapped_;
};

class IceDrink: public Drink {
public:
  IceDrink(const Drink* wrapped): wrapped_(wrapped) {}
  double getPrice() const override { return 0.10 + wrapped_->getPrice();} 
  string getName() const override {return "Ice  " + wrapped_->getName();}
private:
  const Drink *wrapped_;
};





// forward declarations
//DrinkType getDrinkType(); 
//char getTopping();

int main() {
  Drink* d;
  //DrinkType dt = getDrinkType();
  while (true) {
    char input = getChar("Welcome to Coffee Shack, can I get you a [l]arge, [m]edium, or [s]mall coffee ? ");
    // convert to lower case
    input = tolower(input);
    // check if input is valid
    if      (input == 'l')  {d = new Drink(DrinkType::large);   break;}
    else if (input == 'm')  {d = new Drink(DrinkType::medium);  break;}
    else if (input == 's')  {d = new Drink(DrinkType::small);   break;}
    else                    cout << "\tInvalid. options are [s,m,l]" << endl;
  }

  //Drink* d = new Drink(dt);

  while (true) {
    char input = getChar("Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce or [n]ot ? ");

    if      (input == 's')  d = new SprinkledDrink(d);
    else if (input == 'c')  d = new CaramelDrink(d);
    else if (input == 'f')  d = new MilkFoamDrink(d);
    else if (input == 'i')  d = new IceDrink(d);
    else if (input == 'n')  break;
    else                    cout << "\tInvalid. options are: [s,c,f,i,n]" << endl;
  }

  // get customers name
  cout << "Can I get your name? ";
  string name;
  cin >> name;

  print(name);
  print(", your ");
  print(d->getSize());
  print(" coffee");

  if (d->getName() != "") {
    std::stringstream iss(d->getName());
    std::stringstream withCommas;
    string topping; 
    while (iss >> topping) {
      withCommas << topping << ", ";
    }
    string outputWithCommas = withCommas.str();
    outputWithCommas.pop_back();
    outputWithCommas.pop_back();
    cout << " with " << outputWithCommas;
  }
  cout << " is ready. It will be ";
  string priceStr = std::to_string(d->getPrice());
  priceStr = priceStr.substr(0,4);
  cout<< "$" << priceStr << " please." << endl;

  //cout << "" << d->getName() << endl;
  //dprint(name);
  //dprint(coffeeSize);
//  nsio::print("toppings", toppings);
  //cout << "price=" << d->getPrice() << endl;

  delete d;
  
}

*/
/*
DrinkType getDrinkType() {
  char input;
  while (true) {
    input = getChar("Welcome to Coffee Shack, can I get you[l]arge, [m]edium, or [s]mall coffee ? ");
    // convert to lower case
    input = tolower(input);
    // check if input is valid
    if      (input == 'l')
      return DrinkType::large;
    else if (input == 'm') 
      return DrinkType::medium;
    else if (input == 's') 
      return DrinkType::small;
    else 
      cout << "\tInvalid. options are [s,m,l]" << endl;
  }
}
*/
/*
char getTopping() {
  char topping;
  while (true){
    topping = getChar("Would you like to add[s]prinkles, [c]aramel, milk[f]oam, [i]ce or [n]ot ? ");
    // convert to lower case
    topping = tolower(topping);
    // check if input is valid
    if (topping == 's' || topping == 'c' || topping == 'f' || topping == 'i' || topping == 'n') 
      break;
    else 
      cout << "\tInvalid. options are: [s,c,f,i,n]" << endl;
  }
  return topping;
}
*/


/*
A "Coffee Shack" serves coffee to its customers that is composed of 
  the base coffee: large ($3.00), medium ($2.00) or small ($1.00) and 
  added ingredients: sprinkles ($.50), caramel ($.20), milk foam ($.40), ice ($0.10). 
    The ingredients can be added in any order and multiple times. 
  
Here is an example dialog for the order:
  Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee? m
  Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce or [n]ot? s
  Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce or [n]ot? f
  Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce or [n]ot? f
  Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce or [n]ot? n
  Can I get your name? Alex
  Alex, your medium coffee with sprinkles, foam, foam is ready. It will be $3.30, please.

Code the service of "Coffee Shack" program using Decorator Design Pattern.

Extend your program as follows. 
In "Coffee Shack", the barista takes the customers' order and then prepares their drunks. 
The barista may serve her customers concurrently. 
Once the drink is ready, the customers are notified. 
Specifically, after taking an order, the barista randomly either 
  notifies all customers that of one the drinks is ready or 
  starts taking a new order. 
The drinks are not necessarily prepared in the FIFO order.
Code the service of "Coffee Shack" using Observer Design Pattern. 
Customer objects should be registering with Barista object and be notified when a drink is ready. 
All customers could be notified at once. 
Then, each customer should determine if it is her drink.

Extend Barista class so that it contains three different experience levels: 
  JuniorBarista, SeniorBarista, Manager. 
    Junior Barista may only prepare drinks with no added ingredients. 
    Senior Barista may handle all added ingredients except for milk foam. 
    Manager may handle all ingredients. 
    
Implement your barista class using Chain of Responsibility design pattern. 
In your dialog make sure to print the experience level of the barista preparing the order.



// from whiteboard
class sprinckledDrink::DrinkS
  int getPrice(){
    return base->getPrecice()+5;
  }
  Drink* base;
}





*/