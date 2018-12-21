// implementation of carFactory
// Mikhail Nesterenko
// 7/16/2014

#include <array>
#include <cstdlib>
#include "carFactory.hpp"
#include "car.hpp"

// factory methods
Car* CarFactory::requestCar() {
  ++numCarsInProduction_;
  return makeCar();
}

Car* FordFactory::makeCar() {
  return new FordCar();
}

Car* ToyotaFactory::makeCar() {
  return new ToyotaCar();
}