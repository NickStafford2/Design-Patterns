# **************************************************
# Variables to control Makefile operation
CPP = clang++
OPTS = -g -std=c++11

# add any additional tests here
TESTS = test.cpp

# **************************************************

# create executable
main: mainfile.o WordList.o
# list object files that executable depends on 
	$(CPP) $(OPTS) -o WordList mainfile.o WordList.o



# make knows that .o files come from their corrispoinding cpp files
# all we need is 
WordList.o: WordList.h WordList.cpp
	$(CPP) $(OPTS) -c WordList.cpp


#make mainfile
mainfile.o: mainfile.cpp  WordList.h
	$(CPP) $(OPTS) -c mainfile.cpp


# compile the testfile assigned by professor 
test: test.o WordList.o
	$(CPP) $(OPTS) -o test WordList.o test.o


test.o: test.cpp WordList.h
	$(CPP) $(OPTS) -c test.cpp


#########################
clean:
	rm -f *.o
	rm -f *.h.gch
	rm -f *~
