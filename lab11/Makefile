#lab 11 Makefile

CPP = clang++ -std=c++11
OBJECTS = state.o process.o utilities.o scheduler.o main.o

run: all
	./cpuScheduler

fast: all
	./cpuScheduler fast

all: $(OBJECTS)
	$(CPP) -o cpuScheduler $(OBJECTS)

main.o: main.cpp scheduler.hpp state.hpp process.hpp utilities.hpp
	$(CPP) -c main.cpp 

state.o: state.hpp state.cpp process.hpp
	$(CPP) -c state.cpp

process.o: process.hpp process.cpp utilities.hpp 
	$(CPP) -c process.cpp

utilities.o: utilities.hpp utilities.cpp
	$(CPP) -c utilities.cpp

scheduler.o: scheduler.hpp scheduler.cpp state.hpp process.hpp utilities.hpp
	$(CPP) -c scheduler.cpp

clean: 
	rm -f *.o
	rm -f cpuScheduler



