#ifndef CS3_CARLOT_
#define CS3_CARLOT_

#include "carFactory.hpp"
#include "car.hpp"
#include <array>
#include <algorithm>
#include <string>
#include <vector>

// lot may hold up to 4 cars
// lot is initially empty
class CarLot {
public:
  CarLot(string location);
  ~CarLot();
  Car* testDriveCar();
  bool isCarOnLot();

  void startOver();
  Car* nextCar();
  bool lotFull();

  Car* sellCar();
  string getLocation();

private:
  const string kLocation;
  const static int ksMaxCarsOnLot = 4;
  std::vector<Car*> carsOnLot_;
  vector<CarFactory *> factories_;
  int currentTestCarIndex; // index value in carsOnLot_ vector
};

#endif // !CS3_CARLOT_


  // creates 2 Ford factories and 2 Toyota factories 
  /*factories_.push_back(new FordFactory());
  factories_.push_back(new ToyotaFactory());
  factories_.push_back(new FordFactory());
  factories_.push_back(new ToyotaFactory());
  */
  // gets the first car for sale
  //car4sale_ = factories_[rand() % factories_.size()]->requestCar();



// find car

//Car* bought = car4sale_;
//car4sale_ = factories_[rand() % factories_.size()]->requestCar();
//return std::find(carsOnLot_.begin(), carsOnLot_.end(), []() {return true; });



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