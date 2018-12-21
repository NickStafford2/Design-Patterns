# makefile for lab 10 by Nicholas Stafford
CSS = clang++ -std=c++11 
border = "--------------------------------------------------------------"

make: adapter bridge
	@echo $(border)
	@echo "Lab 10 Bridge Painted Square: "
	./bridge
	@echo "\n" $(border)
	@echo "Lab 10 Adapter Moving Square: "
	./adapter

adapter: AdapterClass.cpp nsio.cpp
	$(CSS) -o adapter AdapterClass.cpp nsio.cpp

bridge: bridgeFigures.cpp nsio.cpp
	$(CSS) -o bridge bridgeFigures.cpp nsio.cpp

nsio: nsio.cpp nsio.hpp
	$(CSS) -c nsio.cpp

clean: 
	rm -f adapter
	rm -f bridge
