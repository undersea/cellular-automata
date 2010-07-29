#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

#include <algorithm>
//#include <map>
//#include <set>

using namespace std;

#include "cell.hpp"
#include "graph.hpp"
#include "cellular-automata.hpp"

namespace CellulaAutomata
{
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
  for(unsigned x = 0; x < graph.width; x++) {
    for(unsigned y = 0; y < graph.height; y++) {
      calculate(x, y);
    }
  }
  graph = graph2;
}

Graph CellularAutomata::get(void) const
{
  return graph;
}

void CellularAutomata::set(Graph &grid)
{
  graph = grid;
}


Graph &CellularAutomata::operator () (void)
{
  return graph;
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
  std::set<int> classes = graph.generate_classes();
  //3 above cell
  if(y > 0) {
    if(x > 0) {
      val[graph(x-1,y-1).get()] += 1;
    }
    val[graph(x,y-1).get()] += 1;

    if(x < (graph.width - 1)) {
      val[graph(x+1, y-1).get()] += 1;
    }
  }
  //left of cell
  if(x > 0) {
    val[graph(x-1, y).get()] += 1;
  }
  //right of cell
  if(x < (graph.width - 1)) {
    val[graph(x+1, y).get()] += 1;
  }
  //bottom 3
  if(y < (graph.height - 1)) {
    if(x > 0) {
      val[graph(x-1, y+1).get()] += 1;
    }
    val[graph(x, y+1).get()] += 1;
    if(x < (graph.width - 1)) {
      val[graph(x+1, y+1).get()] += 1;
    }
  }


  int denominator = 1;

  best = for_each(val.begin(), val.end(), find_best< pair<const int, int> >());
  

  if(best.even && val.size() > 1) {
    //randomly assign
    int tmp = rand() % classes.size();
    graph2(x, y).set(tmp);
    printf("rand for {%d,%d} of %d\n", x, y, tmp);
  } else {
    if(best.best_value != 0) {
      graph2(x, y).set(best.best_value);
    }
  }
}

  template<class T> struct print : public unary_function<T, void>
  {
    void operator () (T x) { printf("%d", x); }
  };
}

int main(void)
{
  CellulaAutomata::CellularAutomata graph(25, 25);
  int i,j;
  

  srand(time(NULL));
  int val = 1;
  for(i=0;i<4;i++) {
    unsigned x;
    unsigned y;
    do {
      x = rand()%graph().get_width();
      y = rand()%graph().get_height();
    }while(x == 0 || y == 0 || x == graph().get_width() -1 || y == graph().get_height()); 
    
    
    
    graph()(x-1,y).set(val);
    graph()(x+1,y).set(val);
    graph()(x,y-1).set(val);
    //graph()(x+1,y-1).set(val);
    //graph()(x-1,y-1).set(val);
    graph()(x,y+1).set(val);
    //graph()(x+1,y+1).set(val);
    //graph()(x-1,y+1).set(val);
    graph()(x,y).set(val);
    
    val = i < 2 ? 1 : i < 4 ? 2 : 3;
  }
  set<int> classes = graph().generate_classes();
  printf("number of classes: %d\n", (int)classes.size());
  for(i=0;i<25;i++) {
    for(j=0;j<25;j++) {
      
      printf("%d  ", graph()(i,j).get());
    }
    putchar('\n');
  }
  
  
  //printf("classes:");
  //std::for_each(classes.begin(), classes.end(), CellulaAutomata::print< int >());
  puts("------------------------------------------------------------");
  graph.step();
  graph.step();
  for(i=0;i<25;i++) {
    for(j=0;j<25;j++) {

      printf("%d  ", graph()(i,j).get());
    }
    putchar('\n');
  }

  puts("------------------------------------------------------------");
  graph.step();
  graph.step();
  for(i=0;i<25;i++) {
    for(j=0;j<25;j++) {

      printf("%d  ", graph()(i,j).get());
    }
    putchar('\n');
  }
  puts("------------------------------------------------------------");
  graph.step();
  graph.step();
  for(i=0;i<25;i++) {
    for(j=0;j<25;j++) {

      printf("%d  ", graph()(i,j).get());
    }
    putchar('\n');
  }

  puts("------------------------------------------------------------");
  graph.step();
  graph.step();
  for(i=0;i<25;i++) {
    for(j=0;j<25;j++) {

      printf("%d  ", graph()(i,j).get());
    }
    putchar('\n');
  }
  puts("------------------------------------------------------------");
  graph.step();
  graph.step();
  for(i=0;i<25;i++) {
    for(j=0;j<25;j++) {

      printf("%d  ", graph()(i,j).get());
    }
    putchar('\n');
  }
  puts("------------------------------------------------------------");
  graph.step();
  graph.step();
  for(i=0;i<25;i++) {
    for(j=0;j<25;j++) {

      printf("%d  ", graph()(i,j).get());
    }
    putchar('\n');
  }

  //CellularAutomata automata;
  //automata.set(graph);

  return 0;
}

