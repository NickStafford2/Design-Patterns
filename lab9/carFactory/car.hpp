#ifndef CS3_CAR_
#define CS3_CAR_

#include "brand.hpp"
#include <string>

using std::string;

// abstract product
class Car {
public:
	const Brand* getBrand() const {return brand_;}
  string getModel() const {return model_; }
  
  virtual ~Car() {delete brand_;}

protected:
	Car(Brand* brand) : brand_(brand) {
		model_ = brand_->getRandomModel();
	}
  string model_; // this car's model
  const Brand* brand_;
};

// two concrete products
class FordCar : public Car {
public:
  FordCar() : Car(new Ford()) {} 
  virtual ~FordCar() {}
};

class ToyotaCar : public Car {
public:
  ToyotaCar() : Car(new Toyota()) {}
  virtual ~ToyotaCar() {}
};

#endif // !CS3_CAR_