#cs3 lab 12 Makefile
# Nicholas Stafford


CSS = clang++ -std=c++11 
OPTS = -Wall -pedantic 
OBJECTS = nsio.o main.o 
#drink.o 

run: all
	./CoffeeShack

all: $(OBJECTS)
	$(CSS) -o CoffeeShack $(OBJECTS)

main.o: main.cpp drink.hpp nsio.cpp #barista.hpp customer.hpp # nsio.hpp
	#clang++ -std=c++11 -c main.cpp nsio.cpp drink.hpp
	$(CSS)              -c main.cpp nsio.cpp drink.hpp # barista.hpp customer.hpp # nsio.hpp

#drink.o: drink.hpp #drink.cpp nsio.hpp #drink.hpp 
#	$(CSS) -c drink.hpp #drink.cpp drink.hpp nsio.hpp

nsio.o: nsio.cpp nsio.hpp
	$(CSS) -c nsio.cpp nsio.hpp

clean:
	rm -f *.o
	rm -f *.hpp.gch
	rm -f drink
	rm -f CoffeeShack
	rm -f a.out