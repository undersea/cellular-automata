#include <cstdio>
#include <cstring>

#include "cell.hpp"
#include "graph.hpp"
#include "cellular-automata.hpp"


CellularAutomata::CellularAutomata(void)
{}

CellularAutomata::CellularAutomata(unsigned width, unsigned height)
  : graph(width, height), graph2(width, height)
{}

CellularAutomata::~CellularAutomata(void)
{}

void CellularAutomata::init(unsigned width, unsigned height)
{
  Graph g(width, height);
  Graph g2(width, height);
  this->graph = g;
  this->graph2 = g2;
}


void CellularAutomata::step(void)
{}

Graph CellularAutomata::get(void) const
{
  return graph;
}

void CellularAutomata::set(Graph &grid)
{
  graph = grid;
}

/**
 * Used to calculate the value of the grid cell at position (x, y) based upon the following rules
 * 
 *      0      : class 1 + class 2 neighbours = 0
 *      1      : class 1 > class 2 neighbours
 *      2      : class 1 < class 2 neighbours
 * rand({1,2}) : class 1 == class 2 neighbours
 */
void CellularAutomata::calculate(unsigned x, unsigned y)
{
  
}


int main(void)
{
  Graph graph(10, 10);
  int i,j;
  for(i=0;i<10;i++) {
    for(j=0;j<10;j++) {
      //graph(i,j).set((i+1)*(j+1));
      printf("%d\t", graph(i,j).get());
    }
    putchar('\n');
  }

  CellularAutomata automata;
  automata.set(graph);

  return 0;
}

