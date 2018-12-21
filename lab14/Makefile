# lab 14 makefile. 
#nicholas Stafford

CPP = clang++ -std=c++11
OBJECTS = main.o documentEditor.o document.o command.o


run: $(OBJECTS) documentEditor
	./documentEditor

documentEditor: $(OBJECTS) 
	$(CPP) -o documentEditor $(OBJECTS) 

main.o: main.cpp memento.hpp documentEditor.hpp	document.hpp
	$(CPP) -c main.cpp memento.hpp

documentEditor.o: documentEditor.cpp documentEditor.hpp document.hpp command.hpp
	$(CPP) -c documentEditor.cpp

document.o: document.cpp document.hpp
	$(CPP) -c document.cpp

command.o: command.cpp command.hpp
	$(CPP) -c command.cpp command.hpp document.hpp

clean: 
	rm -f *.o
	rm -f documentEditor

