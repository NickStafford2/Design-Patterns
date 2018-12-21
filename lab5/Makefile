# makefile for lab 5

CC = clang++
OPTS = -std=c++11 -Wall

# List all classes here:
ALL_CLASSES = cs1.txt cs2.txt cs3.txt cs4.txt

main: roster.cpp
	$(CC) $(OPTS) -o listStudentsInClasses roster.cpp
	./listStudentsInClasses $(ALL_CLASSES)

