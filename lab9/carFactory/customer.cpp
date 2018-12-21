// needed for lab
// Mikhail Nesterenko
// 3/14/2016

#include "carLot.hpp"
#include "car.hpp"
#include "customer.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>

using std::vector;
using std::cout; 
using std::endl;



Customer::Customer(string name, Brand* brand) : name_(name) {
  favoriteBrand_ = brand;
  favoriteModel_ = brand->getRandomModel();
  myCar = nullptr;
}

Customer::~Customer(){
  myCar = nullptr;
}

bool Customer::searchLotForCar(CarLot& lot){
  cout <<"\nSearching for a " 
       << favoriteBrand_->getName() << " " 
       << favoriteModel_ 
       << " at " << lot.getLocation() << " Car Lot" << endl;
  lot.startOver();

  int n=1;
  while (!lot.lotFull()){

    Car* toBuy = lot.nextCar();
    string brandName = toBuy->getBrand()->getName();
    string model = toBuy->getModel();

    cout <<"  looking at Car " << n << ": " << brandName << " " << model << endl;
    if (doILikeCar(toBuy)) {
     myCar = lot.sellCar();
     cout << "  purchased car" << endl;
      //delete toBuy;
      return true; 
    }
    ++n;
    //delete toBuy;
  }
  cout <<"Leaving lot, did not find car" << endl;
  return false;

}

bool Customer::doILikeCar(Car* c) {
  string brandName = c->getBrand()->getName();
  string model = c->getModel();

  if (brandName == favoriteBrand_->getName() && model == favoriteModel_)
    return true;
  else 
    return false;
}

/*
///////////////////////////////////////////////////////////////////////////////
The car buyers may now request a particular model as well as the make a car
(randomly selected). 

the dealer lot may hold up to 4 cars. 

The lot may not hold more than four cars. 

The lot is initially empty. 

If the buyer finds the make and model of the car on the lot, 
the buyer buys it and takes from the lot.

Otherwise, the buyer forces the dealer to request a car until the appropriate
model arrives. 

If the wrong make or model is sent, the buyer (not liking it)
makes the dealer leave it on the lot. 

If the lot is full, the buyer goes away
(the buyer function terminates).

Specifically, create three new methods of CarLot class called 
  - nextCar() and
  - startOver() and 
  - lotFull(). 

Modify the carbuyer function as follows. 
  - First, the function invokes startOver(). 
  - Then, the buyer takes the car for a drive with nextCar(). 
  - The buyer contines to do that, until either the buyer finds the make
    and model he likes or the lot is full.
///////////////////////////////////////////////////////////////////////////////
*/
