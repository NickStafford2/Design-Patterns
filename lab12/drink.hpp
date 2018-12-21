#ifndef CS3_DRINK_H_
#define CS3_DRINK_H_

// drink class to be used in Coffee Shack lab
// Mikhail Nesterenko
// 11/15/2016
//
// Use this header file to define your base class.

//#include "drink.hpp"
//#include "nsio.hpp" // my personal repository for easy input and output
#include <iostream>
//#include <ctype.h> // for tolower()
#include <string>
//#include <sstream>      // std::istringstream

//#include <vector>

//using std::cout;
//using std::endl;
//using std::cin;
//using nsio::getChar;
//using nsio::print;
//using nsio::println;
using std::string;

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
  virtual string getToppings() const {return "";}
  virtual string getSize() const {return size_;}
  void   setNameOnCup(string name) {nameOnCup_ = name;}
  string getNameOnCup() {return nameOnCup_;}
private: 
  string nameOnCup_;
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
  string getToppings() const override {return "Sprinkles " + wrapped_->getToppings();}
private:
  const Drink *wrapped_;
};


class CaramelDrink: public Drink {
public:
  CaramelDrink(const Drink* wrapped): wrapped_(wrapped) {}
  double getPrice() const override { return 0.20 + wrapped_->getPrice();} 
  string getToppings() const override {return "Caramel " + wrapped_->getToppings();}
private:
  const Drink *wrapped_;
};

class MilkFoamDrink: public Drink {
public:
  MilkFoamDrink(const Drink* wrapped): wrapped_(wrapped) {}
  double getPrice() const override { return 0.40 + wrapped_->getPrice();} 
  string getToppings() const override {return "Foam " + wrapped_->getToppings();}
private:
  const Drink *wrapped_;
};

class IceDrink: public Drink {
public:
  IceDrink(const Drink* wrapped): wrapped_(wrapped) {}
  double getPrice() const override { return 0.10 + wrapped_->getPrice();} 
  string getToppings() const override {return "Ice  " + wrapped_->getToppings();}
private:
  const Drink *wrapped_;
};




/*
#include <string>

enum class DrinkType { small, medium, large };

class Drink {
public:
  Drink(DrinkType type = DrinkType::small, int price = 0) : type_(type), price_(price) {}
  virtual int getPrice() const;
  virtual std::string getToppings() const;
private:
  DrinkType type_;
  int price_;
};
*/

/*

// first decorator
class BoldParagraph : public DrinkType {
public:
  BoldDrinkType(const DrinkType* wrapped): wrapped_(wrapped) {}
  string getHTML() const override {
    return "<b>" + wrapped_->getHTML() + "</b>";
  }
private:
  const DrinkType *wrapped_;
};
*/






#endif // !CS3_DRINK_H_
