CPP=g++
CPPFLAGS=-I. -g

test: containerBIT.cpp
	$(CPP) $(CPPFLAGS) -o test containerBIT.cpp

clean: 
	rm test
