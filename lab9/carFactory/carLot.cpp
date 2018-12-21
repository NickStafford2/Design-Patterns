#include "carFactory.hpp"
#include "car.hpp"
#include "carLot.hpp"


//#include <array>
//#include <algorithm>
#include <string>
#include <iostream>

CarLot::CarLot(string location) : kLocation(location) {
  factories_.push_back(new FordFactory());
  factories_.push_back(new ToyotaFactory());
  currentTestCarIndex = -1;
}
CarLot::~CarLot() {
	for (int i = 0; i < factories_.size(); ++i)
    delete factories_[i];
}
string CarLot::getLocation(){
  return kLocation;
}


Car* CarLot::testDriveCar() { 
  return carsOnLot_[currentTestCarIndex];
}


void CarLot::startOver() {
  carsOnLot_.clear(); 
  currentTestCarIndex = -1;
}

Car* CarLot::nextCar() {
  //if (carsOnLot_.size() <= currentTestCar) {
  
    carsOnLot_.push_back(factories_[rand() % factories_.size()]->requestCar());

  ++currentTestCarIndex;
  return carsOnLot_[carsOnLot_.size() -1]; // most recently ordered car
}
bool CarLot::lotFull() {
  return (currentTestCarIndex >= ksMaxCarsOnLot -1);
}

Car* CarLot::sellCar() {
  Car* c = carsOnLot_[currentTestCarIndex];
  carsOnLot_.erase(carsOnLot_.begin() + currentTestCarIndex);
  return c;
}

