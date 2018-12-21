// Nicholas Stafford
// lab 9
// factory method example
//

#include <iostream>
#include <vector>
#include "brand.hpp"
#include "car.hpp"
#include "carFactory.hpp"
#include "customer.hpp"
#include "carLot.hpp"
//#include <memory>

using std::cout;
using std::endl;
using std::vector;

void printPurchase(Customer& c) {
  cout << "\n"
       << c.getName() << " now owns a " 
       << c.getCar()->getBrand()->getName() << " "
       << c.getCar()->getModel() << endl;
}

int main() {
  //std::unique_ptr<Brand> ford(new Ford());
  //std::unique_ptr<Brand> toyota(new Toyota());
  Brand* ford = new Ford();
  Brand* toyota = new Toyota();
	std::srand(time(nullptr));

  cout << "\n3 customers: Bob, Sam, Jon" << endl;
  vector<Customer> customers;

   customers.push_back(Customer("Bob", (rand()%2 == 0) ? ford : toyota));
   customers.push_back(Customer("Sam", (rand()%2 == 0) ? ford : toyota));
   customers.push_back(Customer("Jon", (rand()%2 == 0) ? ford : toyota));

  cout << "\n3 carLots in Kent, New York, and Chicago\n" << endl;
  vector<CarLot> lots;
  CarLot lot1("Kent");
  CarLot lot2("New York");
  CarLot lot3("Chicago");

  cout << "Each customer will visit the lots and attempt to buy a car" << endl;

  for (Customer& c: customers) {
    cout << "----------------------------------------------------------------------\n";
    cout << c.getName() << "'s favorite brand and model: "  
     << c.getFavoriteBrand()->getName() << " " 
     << c.getFavoriteModel() << endl;

    if (c.searchLotForCar(lot1))
      printPurchase(c);
    else if (c.searchLotForCar(lot2))
      printPurchase(c);
   else if (c.searchLotForCar(lot3))
      printPurchase(c);
    else 
      cout << c.getName() 
           << " could not find car at any of the lots. Try again later.\n" << endl;
 
  }
  cout << "----------------------------------------------------------------------\n";
  delete ford;
  delete toyota;
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
