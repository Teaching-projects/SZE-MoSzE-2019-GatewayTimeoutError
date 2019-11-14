OBJS=ancestor.o directory.o file.o filesystem.o main.o
CXXFLAGS=-O2 -std=c++11

all: $(OBJS)
	g++ -o terminal $(OBJS)
main.o: main.cpp filesystem.h
	g++ -c main.cpp $(CXXFLAGS)
directory.o: directory.cpp directory.h file.h ancestor.h
	g++ -c directory.cpp $(CXXFLAGS)
file.o: file.cpp file.h ancestor.h
	g++ -c file.cpp $(CXXFLAGS)
filesystem.o: filesystem.cpp filesystem.h directory.h
	g++ -c filesystem.cpp $(CXXFLAGS)
ancestor.o: ancestor.cpp ancestor.h
	g++ -c ancestor.cpp $(CXXFLAGS)
clean:
	rm -f *.o