#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

#include <algorithm>
//#include <map>
//#include <set>

#include <fstream>

using namespace std;

#include "cell.hpp"
#include "graph.hpp"
#include "cellular-automata.hpp"
#include "coord.hpp"

namespace CellularAutomata
{
  CellularAutomata::CellularAutomata(void)
  {}

  /*CellularAutomata::CellularAutomata(unsigned width, unsigned height)
    : graph(width, height), graph2(width, height)
    {}*/

  CellularAutomata::~CellularAutomata(void)
  {}

  /*void CellularAutomata::init(unsigned width, unsigned height)
  {
    Graph g(width, height);
    Graph g2(width, height);
    this->graph = g;
    this->graph2 = g2;
    }*/


  void CellularAutomata::step(void)
  {
    /*for(unsigned x = 0; x < graph.width; x++) {
      for(unsigned y = 0; y < graph.height; y++) {
	calculate(x, y);
      }
      }*/
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
   * Using Von Neumann method of being influenced by the north, south, east and west.
   * Used to calculate the value of the grid cell at position (x, y) based upon the following rules
   * 
   *      0      : class 1 + class 2 neighbours = 0
   *      1      : class 1 > class 2 neighbours
   *      2      : class 1 < class 2 neighbours
   * rand({1,2}) : class 1 == class 2 neighbours
   * for the moment will not wrap the grid so ignore any x value < 0 or > width and y values < 0 or >  height.
   */
  /*void CellularAutomata::calculate(unsigned x, unsigned y)
  {
    map<int, int> val;
    find_best< pair<const int, int> > best;
    std::set<int> classes = graph.generate_classes();
    //3 above cell
    if(y > 0) {
      //    if(x > 0) {
      //  val[graph(x-1,y-1).get()] += 1;
      //}
      val[graph(x,y-1).get()] += 1;

      //if(x < (graph.width - 1)) {
      //  val[graph(x+1, y-1).get()] += 1;
      //}
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
      //if(x > 0) {
      //  val[graph(x-1, y+1).get()] += 1;
      //}
      val[graph(x, y+1).get()] += 1;
      //if(x < (graph.width - 1)) {
      //  val[graph(x+1, y+1).get()] += 1;
      //}
    }


    best = for_each(val.begin(), val.end(), find_best< pair<const int, int> >());
  

    if(best.even) {
      //randomly assign
      int tmp = rand() % classes.size();
      graph2(x, y).set(tmp);
      printf("rand for {%d,%d} of %d\n", x, y, tmp);
    } else {
      if(best.best_value != 0) {
	graph2(x, y).set(best.best_value);
	//printf("set {%d, %d} to %d\n", x,y,best.best_value);
      } else {
	graph2(x, y).set(graph(x,y).get());
      }
    }
  }
  */
  template<class T> struct print : public unary_function<T, void>
  {
    void operator () (T x) { printf("%d", x); }
  };
} // namespace CellularAutomata

int main(void)
{
  CellularAutomata::CellularAutomata graph;
  int i,j;
  ifstream input;
  
  input.open("points.txt");
  //graph().load(input);
  input.close();

  //set<int> classes = graph().generate_classes();
  //printf("number of classes: %d\n", (int)classes.size());
  for(i=0;i<25;i++) {
    for(j=0;j<25;j++) {
      CellularAutomata::Coord coord;
      coord[0] = i;
      coord[1] = j;
      printf("%d  ", graph()(coord).get());
    }
    putchar('\n');
  }
  
  
  //printf("classes:");
  //std::for_each(classes.begin(), classes.end(), CellulaAutomata::print< int >());
 

  return 0;
}

