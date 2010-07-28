CC=g++
CXX=g++

CFLAGS=-pedantic -ansi -Wall
CXXFLAGS=$(CFLAGS)

OBJECTS=src/cellular-automata.o src/cell.o src/graph.o


all: main

main: $(OBJECTS)
	g++ -o cellula-automata $(OBJECTS)

clean:
	$(RM) $(OBJECTS)