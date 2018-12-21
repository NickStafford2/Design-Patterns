#include "brand.hpp"
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>

using std::string;

string Brand::getRandomModel() const { 
  int r = std::rand() % models_.size();
  return models_[r];
}

Brand::~Brand() {
	//delete models_;
}