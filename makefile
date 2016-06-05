CXX=g++
CXXFLAGS=-Wall -g -std=c++14
LINK_FLAGS=-lgtest -lgmock -pthread

tests: TestMain.o MatrixTests.o Matrix.o
	$(CXX) -o tests TestMain.o MatrixTests.o Matrix.o $(LINK_FLAGS)

TestMain.o: test/TestMain.cpp MatrixTests.o
	$(CXX) $(CXXFLAGS) -c test/TestMain.cpp
	
MatrixTests.o: test/MatrixTests.cpp Matrix.o
	$(CXX) $(CXXFLAGS) -c test/MatrixTests.cpp

Matrix.o: src/Matrix.h src/Matrix.cpp
	$(CXX) $(CXXFLAGS) -c src/Matrix.cpp

clean:
	rm *.o tests
