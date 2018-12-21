// interface for abstract and concrete car factories
// Nicholas Stafford
// Based on code originally from Mikhail Nesterenko
// 7/16/2014

#ifndef CS3_CAR_FACTORY_
#define CS3_CAR_FACTORY_

#include <string>
#include "car.hpp"

using std::string;

// absract factory
class CarFactory {
public:
  CarFactory(string location, int numCarsInProduction) :
    location_(location),
    numCarsInProduction_(numCarsInProduction) {}

  Car* requestCar();
  string getLocation() const { return location_; }
  int getNumCarsInProduction() const {return numCarsInProduction_;}
  virtual ~CarFactory() {}
protected:
  virtual Car* makeCar() = 0;

private:
  string location_;
  int numCarsInProduction_;
};


// two concrete factories
class FordFactory : public CarFactory {
public:
  FordFactory(string location = "", int numCarsInProduction = 0) :
    CarFactory(location, numCarsInProduction) {}
protected:
  Car* makeCar();
};

class ToyotaFactory : public CarFactory {
public:
  ToyotaFactory(string location = "", int numCarsInProduction = 0) :
    CarFactory(location, numCarsInProduction) {}
protected:
  Car* makeCar();
};
#endif // !CS3_CAR_FACTORY_
