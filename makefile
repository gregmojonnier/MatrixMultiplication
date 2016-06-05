CXX=g++
CXXFLAGS=-Wall -g -std=c++14
LINK_FLAGS=-lgtest -lgmock -pthread

tests: test_main.o
	$(CXX) -o tests test_main.o $(LINK_FLAGS)

test_main.o: test_main.cpp
	$(CXX) $(CXXFLAGS) -c test_main.cpp
	
