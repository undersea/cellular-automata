#include <cstdio>
#include <cstring>

#include <algorithm>
#include <map>

using namespace std;

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
{
  
}

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
 * for the moment will not wrap the grid so ignore any x value < 0 or > width and y values < 0 or >  height.
 */
void CellularAutomata::calculate(unsigned x, unsigned y)
{
  map<int, int> val;
  find_best< pair<const int, int> > best;
  //3 above cell
  if(y > 0) {
    if(x > 0) {
      val[graph(x-1,y-1).get()] += 1;
    }
    val[graph(x,y-1).get()] += 1;

    if(x < (width - 1)) {
      val[graph(x+1, y-1).get()] += 1;
    }
  }
  //left of cell
  if(x > 0) {
    val[graph(x-1, y).get()] += 1;
  }
  //right of cell
  if(x < (width - 1)) {
    val[graph(x+1, y).get()] += 1;
  }
  //bottom 3
  if(y < (height - 1)) {
    if(x > 0) {
      val[graph(x-1, y+1).get()] += 1;
    }
    val[graph(x, y+1).get()] += 1;
    if(x < (width - 1)) {
      val[graph(x+1, y+1).get()] += 1;
    }
  }


  best = for_each(val.begin(), val.end(), find_best< pair<const int, int> >());

  graph2(x, y).set(best.best_value);
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

