// nicholas Stafford
// main file

#include "drink.hpp"
//#include "barista.hpp"
//#include "customer.hpp"
#include "nsio.hpp" // my personal repository for easy input and output
#include <iostream>
#include <ctype.h> // for tolower()
#include <string>
#include <sstream>      // std::istringstream
#include <stdlib.h> 
#include <set>
#include <vector>

using std::cout;
using std::endl;
using std::cin;
using nsio::getChar;
using nsio::print;
using nsio::println;
using std::string;

using std::vector;
using std::set;

// subject in observer design pattern
//class Barista;

// anyone in resturant can access
vector<Drink*> drinks;


class Customer {
public:
  Customer();
  void notify(Drink*);
  void setName(string name) {name_ = name;}
  string getName() {return name_;}
  bool hasBeenServed() {return hasBeenServed_;}
  void serve() {hasBeenServed_ = true;}
private:
  string name_;
  bool hasBeenServed_;
};

set<Customer*> customers_; // observers
// reciever in chain of responcibility design pattern
class Barista {
public:
  Barista(Barista *successor = nullptr) : successor_(successor) {}
  virtual void takeOrder(Customer *o)=0;
  //void registerCustomer(Customer *o);
  void deregisterCustomer(Customer *o) {customers_.erase(o);}
  void notifyCustomers();

protected:
  //set<Customer*> customers_; // observers
  //vector<Drink*> drinks;
  Barista* successor_;
};

class JuniorBarista: public Barista {
public:
  JuniorBarista(Barista *successor = nullptr) : Barista(successor){}
  void takeOrder(Customer *c) override;
};

class SeniorBarista: public Barista {
public:
  SeniorBarista(Barista *successor = nullptr) : Barista(successor){}
  void takeOrder(Customer *c) override;
};

class ManagerBarista: public Barista {
public:
  ManagerBarista(Barista *successor = nullptr) : Barista(successor){}
  void takeOrder(Customer *c) override;
};

Customer::Customer() : hasBeenServed_(false) {

}

void JuniorBarista::takeOrder(Customer *c) {

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

  char wantToppings = getChar("Would you like any toppings? [y,n]") ;
  if (wantToppings == 'y') {
    cout << "I don't know how to add toppings, calling a senior Barista." << endl;
    drinks.push_back(d);
    successor_->takeOrder(c);
  }
  else {
    // get customers name
    cout << "Can I get your name? ";
    string name;
    cin >> name;
    c->setName(name);
    d->setNameOnCup(name);
  
    // tell customer the price 
    cout << "That will be ";
    string priceStr = std::to_string(d->getPrice());
    priceStr = priceStr.substr(0,4);
    cout<< "$" << priceStr << " please." << endl;
  
    cout << "Thank you for ordering. please wait" << endl;
  
    customers_.insert(c);
    drinks.push_back(d);

    // finished taking customers order
  }
}

void SeniorBarista::takeOrder(Customer *c) {
  //cout << "senior take order called" << endl;
  const string spacer = "   ";
  /*for (Drink* dp: drinks) {
    cout << "got it" << endl;
  }*/
  //cout << "after for " << endl;
  Drink* d = drinks.back(); // most recent  drink 
  drinks.pop_back();
  cout << "\n" << spacer << "I am a Senior Barista, I can add most toppings" << endl;
  char input = getChar(spacer + "Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce or [n]ot ? ");
  while (input != 'n' && input != 'f') {

    if      (input == 's')  d = new SprinkledDrink(d);
    else if (input == 'c')  d = new CaramelDrink(d);
    //else if (input == 'f')  d = new MilkFoamDrink(d);
    else if (input == 'i')  d = new IceDrink(d);
    else if (input == 'n')  break;
    //else                    cout << "\t   Invalid. options are: [s,c,f,i,n]" << endl;
    input = getChar(spacer + "Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce or [n]ot ? ");
  }
  if (input == 'f') {
    cout << spacer << "I don't know how to add foam, let me call my manager." << endl;
    drinks.push_back(d);
    successor_->takeOrder(c);
  }
  else {
    // get customers name
    cout << spacer <<"Can I get your name? ";
    string name;
    cin >> name;
    c->setName(name);
    d->setNameOnCup(name);

    // tell customer the price 
    cout << spacer << "That will be ";
    string priceStr = std::to_string(d->getPrice());
    priceStr = priceStr.substr(0,4);
    cout<< spacer << "$" << priceStr << " please." << endl;

    cout << spacer << "Thank you for ordering. please wait" << endl;

    customers_.insert(c);
    drinks.push_back(d);
    // finished taking customers order
    
  }
}


void ManagerBarista::takeOrder(Customer *c) {
  //cout << "senior take order called" << endl;
  const string spacer = "       ";
  /*for (Drink* dp: drinks) {
    cout << "got it" << endl;
  }*/
  //cout << "after for " << endl;
  Drink* d = drinks.back(); // most recent  drink 
  drinks.pop_back();
  cout << "\n" << spacer << "I am a Manager Barista, I can add foam" << endl;
  d = new MilkFoamDrink(d);
  cout << spacer << "Foam added. Anything else?" << endl;
  while (true) {
    char input = getChar(spacer + "Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce or [n]ot ? ");

    if      (input == 's')  d = new SprinkledDrink(d);
    else if (input == 'c')  d = new CaramelDrink(d);
    else if (input == 'f')  d = new MilkFoamDrink(d);
    else if (input == 'i')  d = new IceDrink(d);
    else if (input == 'n')  break;
    else                    cout << "\t   Invalid. options are: [s,c,f,i,n]" << endl;
  }

  // get customers name
  cout << spacer <<"Can I get your name? ";
  string name;
  cin >> name;
  c->setName(name);
  d->setNameOnCup(name);

  // tell customer the price 
  cout << spacer << "That will be ";
  string priceStr = std::to_string(d->getPrice());
  priceStr = priceStr.substr(0,4);
  cout<< spacer << "$" << priceStr << " please." << endl;

  cout << spacer << "Thank you for ordering. please wait" << endl;

  customers_.insert(c);
  drinks.push_back(d);
  // finished taking customers order
}


void Barista::notifyCustomers() {
  Drink* readyDrink = drinks[0];

  print(readyDrink->getSize());
  print(" coffee");

  if (readyDrink->getToppings() != "") {
    std::stringstream iss(readyDrink->getToppings());
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
  cout << " is ready for " << readyDrink->getNameOnCup() << "." << endl;

  //cout << "drink is ready" << endl;
  for(auto c: customers_) 
    c->notify(readyDrink);
  drinks.erase(drinks.begin());
}


void Customer::notify(Drink* readyDrink) {
  cout << "   " << name_ << " has been notified" ;
  if (readyDrink->getNameOnCup() == name_) {
    cout << "   This is mine!" << endl;
    hasBeenServed_ = true;
  }
  else {
    cout << "   This is not mine." << endl;
  }
}
// observer in observer design pattern

int main() {
  const int kNumberOfCustomers = 3;
  srand(0);
  //SeniorBarista tom ;
  JuniorBarista sarah(new SeniorBarista(new ManagerBarista));
  vector<Customer*> allCustomers;
  for (int i=0; i < kNumberOfCustomers; ++i) {
    allCustomers.push_back(new Customer());
  }
  //Drink* readyDrink allCustomers;
  int servedCount = 0;
  for (Customer* c: allCustomers) {
    cout << "\nNext Customer Approaches" << endl;
    sarah.takeOrder(c);
    if (rand()%2 == 0) { 
      //drink is ready
      cout << "\n";
      sarah.notifyCustomers();
      ++servedCount;
    }
  }
  for (; servedCount<kNumberOfCustomers; ++servedCount)  {
    cout << "\n";
    sarah.notifyCustomers();
  }

  //Customer John("John", sarah);
  //Customer Dave("Dave", sarah);
  //cout << "Making drink. Next Customer" << endl;
  //Customer Nick("Nick", sarah);
  cout << "\nAll cusomers served." << endl;


  /*
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
  */
}

