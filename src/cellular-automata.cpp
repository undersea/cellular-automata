#include <cstdio>
#include <cstring>

#include "cell.hpp"
#include "graph.hpp"
#include "cellular-automata.hpp"


CellularAutomata::CellularAutomata(void)
{}

CellularAutomata::CellularAutomata(unsigned width, unsigned height)
  : graph(width, height)
{}

CellularAutomata::~CellularAutomata(void)
{}

void CellularAutomata::init(unsigned width, unsigned height)
{
  Graph g(width, height);
  this->graph = g;
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

void CellularAutomata::calculate(unsigned x, unsigned y)
{}


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

