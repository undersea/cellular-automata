#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

#include <typeinfo>

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

  CellularAutomata::CellularAutomata(const std::vector<unsigned short> &dimensions)
    : graph(dimensions), graph2(dimensions)
  {

  }

  CellularAutomata::~CellularAutomata(void)
  {}



  void CellularAutomata::step(void)
  {
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


  void CellularAutomata::step(void)
  {
    Coord start(graph.dimensions.size());
    for(unsigned i = 0; i < graph.dimensions.size(); i++) {
      for(int j = 0; j < graph.dimensions[i]; j++) {
	calculate(coord);
      }
    }
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
  void CellularAutomata::calculate(const Coord &point)
  {
    map<char, char> val;
    find_best< pair<const char, char> > best;

    for(unsigned i = 0; i < point.size(); i++) {
      for(int j = -1; j < 1; j+=2) {
	Coord neighbour = point;
	neighbour[i] += j;
	val[graph(neighbour).get()]++;
      }
    }

    best = for_each(val.begin(), val.end(), find_best< pair<const char, char> >());
  

    if(best.even) {
      //randomly assign
      Short tmp;
      tmp.bits = rand() % graph.klasses.size();
      graph2(point).set(tmp.bits);
    } else {
      if(best.best_value != 0) {
	graph2(point).set(best.best_value);
      } else {
	graph2(point).set(graph(point).get());
      }
    }
  }
  
  template<class T> struct print : public unary_function<T, void>
  {
    void operator () (T x) { printf("%d, ", x); }
  };
} // namespace CellularAutomata




int main(void)
{
  std::cout << "begin\n";
  std::vector<unsigned short> dimensions(8);
  dimensions[0] = 3;
  dimensions[1] = 10;
  dimensions[2] = 10;
  dimensions[3] = 15;
  dimensions[4] = 30;
  dimensions[5] = 16;
  dimensions[6] = 10;
  dimensions[7] = 11;
  dimensions[8] = 30;
  std::cout << "before init graph\n";
  CellularAutomata::CellularAutomata graph(dimensions);
  std::cout << "after init graph\n";
  //int i,j,k;
  ifstream input;
  
  std::cout << "before load\n";
  input.open("data/abalone2.data");
  std::cout << "opened\n";
  graph().load(input, ' ');
  input.close();
  std::cout << "after load\n";

  const std::set<unsigned> classes = graph().generate_classes();
  printf("number of classes: %d\n", (unsigned)classes.size());
  
  
  printf("classes:");
  std::for_each(classes.begin(), classes.end(), 
		CellularAutomata::print< unsigned >());
  putchar('\n');
 

  return 0;
}

