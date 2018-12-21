# Makefile designed to compile and execute testCollection with the
# make command

###################################################################
# Variables
CPP = clang++

OPTS =  -std=c++11

###################################################################
# Commands
main: testCollection.o
	$(CPP) $(OPTS) -o testCollection testCollection.o
	./testCollection

testCollection.o: Collection.h list.h testCollection.cpp
	$(CPP) $(OPTS) -c testCollection.cpp


clean:
	rm -f testCollection.o
