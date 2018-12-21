#makefile for carFactory example of factory design pattern

CPP = clang++ -std=c++11 -pedantic -Wall -g
OPTIONS = main.o car.o brand.o carFactory.o customer.o carLot.o
#make: main.cpp brand.cpp brand.hpp car.cpp car.hpp #carFactory.cpp carFactory.hpp
#	$(CPP) -o testCars main.cpp brand.cpp car.cpp #carFactory.cpp carFactory.hpp

run: all
	./testCars

all: $(OPTIONS)
	$(CPP) -o testCars $(OPTIONS)

main.o: main.cpp car.hpp brand.hpp carFactory.hpp carLot.hpp
	$(CPP) -c main.cpp

car.o: car.cpp car.hpp brand.hpp
	$(CPP) -c car.cpp

brand.o: brand.cpp brand.hpp
	$(CPP) -c brand.cpp

carFactory.o: carFactory.cpp carFactory.hpp car.hpp
	$(CPP) -c carFactory.cpp

customer.o: customer.cpp customer.hpp car.hpp carLot.hpp
	$(CPP) -c customer.cpp

carLot.o: carLot.cpp carLot.hpp car.hpp carFactory.hpp
	$(CPP) -c carLot.cpp

valgrind: all
	valgrind --leak-check=full ./testCars

clean:
	rm -f a.out
	rm -f *.hpp.gch
	rm -f *.o