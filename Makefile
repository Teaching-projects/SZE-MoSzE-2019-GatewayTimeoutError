OBJS=item.o directory.o file.o filesystem.o main.o
CXXFLAGS=-O2 -std=c++11

all: $(OBJS)
	g++ -o terminal $(OBJS)
main.o: main.cpp filesystem.h
	g++ -c main.cpp $(CXXFLAGS)
directory.o: directory.cpp directory.h file.h item.h
	g++ -c directory.cpp $(CXXFLAGS)
file.o: file.cpp item.h
	g++ -c file.cpp $(CXXFLAGS)
filesystem.o: filesystem.cpp filesystem.h directory.h
	g++ -c filesystem.cpp $(CXXFLAGS)
item.o: item.cpp item.h
	g++ -c item.cpp $(CXXFLAGS)
clean:
	rm -f *.o