OBJS=ancestor.o directory.o file.o filesystem.o main.o
CXXFLAGS=-O2 -std=c++11

projekt: $(OBJS)
	g++ -o projekt $(OBJS)
main.o: main.cpp
	g++ -c main.cpp $(CXXFLAGS)
directory.o: directory.cpp
	g++ -c directory.cpp $(CXXFLAGS)
file.o: file.cpp
	g++ -c file.cpp $(CXXFLAGS)
filesystem.o: filesystem.cpp
	g++ -c filesystem.cpp $(CXXFLAGS)
ancestor.o: ancestor.cpp
	g++ -c ancestor.cpp $(CXXFLAGS)
clean:
	rm -f *.o