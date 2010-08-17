#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>

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
  template<class T> struct print : public unary_function<T, void>
  {
    void operator () (T x) { printf("%d, ", x); }
  };


  template<class U> struct progress_count : public unary_function<U, void>
  {
    progress_count(void) : count(0){}
    void operator () (U x) { 
      if(x.get()>0) {count++;} 
      // printf("%d, ", x.get());
    }
    unsigned count;
  };


  CellularAutomata::CellularAutomata(void)
  {}

  CellularAutomata::CellularAutomata(const std::vector<unsigned short> &dimensions)
    : graph(dimensions), graph2(dimensions)
  {

  }

  CellularAutomata::~CellularAutomata(void)
  {}


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
    set(start, 0);
    graph = graph2;
  }


  const bool CellularAutomata::full(void) const
  {
    return progress() == 100;
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
    std::map<char, char> val;
    find_best< std::pair<const char, char> > best;

    for(unsigned i = 0; i < point.size(); i++) {
      for(int j = -1; j < 1; j+=2) {
	Coord neighbour = point;
	neighbour[i] += j;
	if(neighbour[i] >= 0 && neighbour[i] <= graph.dimensions[i]) {
	   val[graph(neighbour).get()]++;
	}
      }
    }

    best = std::for_each(val.begin(), val.end(), find_best< std::pair<const char, char> >());
  
    if(best.even) {
      //randomly assign
      Short tmp(point);
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
  

  void CellularAutomata::set(const Coord &coord, const unsigned c_pos)
  {
    if(c_pos >= coord.size()) {
      return;
    } else {
      Coord point = coord;
      if(c_pos < coord.size() - 1) {
	for(int i = 0; i < graph.dimensions[c_pos]; i++) {
	  point[c_pos] = i;
	  set(point, c_pos+1);
	}
      } else {
	for(int i = 0; i < graph.dimensions[c_pos]; i++) {
	  point[c_pos] = i;
	  calculate(point);
	}
      }
    }
  }


  const unsigned CellularAutomata::progress(void) const
  {
    progress_count<Short> p;
    p = std::for_each(graph.grid.begin(), graph.grid.end(), progress_count< Short >());
    double percent = (((double)p.count)/((double)graph.grid.size()))*100.0;
    return static_cast<unsigned>(round(percent));
  }
 
} // namespace CellularAutomata




int main(void)
{
  std::cout << "begin\n";
  std::vector<unsigned short> dimensions(2);
  dimensions[0] = 80;
  dimensions[1] = 50;

 
  std::cout << "before init graph\n";
  CellularAutomata::CellularAutomata graph(dimensions);
  std::cout << "after init graph\n";
  //int i,j,k;
  ifstream input;
  
  std::cout << "before load\n";
  input.open("data/iris2.data");
  if(input.good()) {
    std::cout << "opened\n";
    graph().load(input, ' ');
    input.close();
  } else {
    perror("Failed to open file");
    return 1;
  }
  std::cout << "after load\n";

  const std::set<unsigned> classes = graph().generate_classes();
  printf("number of classes: %d\n", (unsigned)classes.size());
  
  
  printf("classes: ");
  std::for_each(classes.begin(), classes.end(), 
		CellularAutomata::print< unsigned >());
  putchar('\n');
  printf("Number of dimensions: %d\n", graph().get_number_dimensions());

  unsigned steps = 0;
  printf("is %d%% done\n", graph.progress());
  while(!graph.full()) {
    graph.step();
    steps++;
    if(steps % 1000 == 0) {
      printf("been going for %u steps\n", steps);
      printf("is %d%% done\n", graph.progress());
    }
  }
  
   for(int i = 0; i< 10;i++) {
     graph.step();
   }


  CellularAutomata::Coord coord(2);
  coord[0] = 0;
  coord[1] = 0;

  printf("Value at {0,0} is %d\n", graph()(coord).get());
  return 0;
}

