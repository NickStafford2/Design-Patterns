//carBuyer.hpp
// needed for lab
// Mikhail Nesterenko and Nicholas Stafford
// 3/14/2016

#include "brand.hpp"
#include "carLot.hpp"

class Customer {
public:
  Customer(string name, Brand* brand);
  ~Customer();
  void testCar(CarLot* pCarLot);
  bool doILikeCar(Car* c);
  Car* getCar() const {return myCar;}
  Brand* getFavoriteBrand() {return favoriteBrand_;}
  string getFavoriteModel() {return favoriteModel_;}
  bool searchLotForCar(CarLot& pLot);
  string getName() const {return name_;};
private:
  const string name_;
  Brand* favoriteBrand_;
  string favoriteModel_;
  Car* myCar;
};


/*
///////////////////////////////////////////////////////////////////////////////
The car buyers may now request a particular model as well as the make a car
(randomly selected). the dealer lot may hold up to 4 cars. The lot may not hold
more than four cars. The lot is initially empty. If the buyer finds the make
and model of the care on the lot. the buyer buys it and takes from the lot.
Otherwise, the buyer forces the dealer to request a car until the appropriate
model arrives. If the wrong make or model is sent, the buyer (not liking it)
makes the dealer leave it on the lot. If the lot is full, the buyer goes away
(the buyer function terminates).

Specifically, create three new methods of CarLot class called nextCar() and
startOver() and lotFull(). Modify the carbyer function as follows. First, the
function invokes startOver(). Then, the buyer takes the car for a drive with
nextCar(). The buyer contines to do that, until either the buyer finds the make
and model he likes or the lot is full.
///////////////////////////////////////////////////////////////////////////////
*/