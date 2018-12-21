# Makefile for lab 7 I am still learning makefiles and how compilers
# work. this is practice there are 2 main functions in two files.  I
# am trying to get makefile to execute one if the user types new, and
# another if the user types old. by default, if user types "make", new
# is executed.

# Compiler
CC = clang++ -std=c++11

# Options
OPTS =  -Wall #-pedantic

# Data files
DATA = data.txt data2.txt

# Objects
OBJECTS = hashmap.o 
# Main called if user types "make" and nothing else


default: newTests
	@echo executing default hashmap tests:
	./newTests

tests: newTests oldTests


newTests: hashmap.cpp hashmap.h
	$(CC) -o newTests hashmap.cpp

oldTests: hashmap.h testHashmap.cpp
	$(CC) -o oldTests testHashmap.cpp

options:
	@echo possible commands are:
	@echo new #executes using myTests.cpp
	@echo old #executes using testHashmap.cpp


clean:
	-rm *.o
	-rm *~
	-rm newTests
	-rm oldTests
