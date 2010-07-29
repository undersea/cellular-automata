CC=g++
CXX=g++

CFLAGS=-pedantic -ansi -Wall
CXXFLAGS=$(CFLAGS)

OBJECTS=src/cellular-automata.o src/cell.o src/graph.o

EXENAME=cellula-automata


all: main

main: $(OBJECTS)
	g++ -o $(EXENAME) $(OBJECTS)

clean:
	$(RM) $(OBJECTS) $(EXENAME)