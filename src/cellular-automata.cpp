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

//#define DEBUG2

using namespace std;

#include "cell.hpp"
#include "graph.hpp"
#include "cellular-automata.hpp"
#include "coord.hpp"

namespace CellularAutomata
{
  template<class T> struct print : public unary_function<T, void>
  {
    void operator () (T x) {
	printf("%d ", x);
    }
  };


  template<class T> struct print_Short : public unary_function<T, void>
  {
    print_Short(void) : count(0) {}
    void operator () (T x) {
      if(typeid(x) == typeid(Short)) {
	try {
	  printf("%u: %u, ", count++, x.bits);
	} catch(std::exception e) { 
	  std::cerr << e.what();
	}
      }
    }
    unsigned count;
  };


  template<class U> struct progress_count : public unary_function<U, void>
  {
    progress_count(void) : count(0){}
    void operator () (U x) { 
      if(x.get()!=0) {count++;} 
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
    std::map<unsigned short, unsigned short> val;
    find_best< std::pair<const unsigned short, unsigned short> > best;

    for(unsigned i = 0; i < point.size(); i++) {
      for(int j = -1; j < 2; j+=2) {
	Coord neighbour(point.size());
	neighbour = point;
	neighbour[i] += j;
#ifdef DEBUG
	puts("calculate");
	std::for_each(neighbour.begin(), neighbour.end(), 
		      print< unsigned >());
	putchar('\n');
#endif
	if(neighbour[i] >= 0 && neighbour[i] < graph.dimensions[i]) {
	   val[graph(neighbour).get()]++;
	}
      }
    }

    best = std::for_each(val.begin(), val.end(), find_best< std::pair<const unsigned short, unsigned short> >());
  
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
  

  /**
   * CellularAutomata::set
   */

  void CellularAutomata::set(const Coord &coord, const unsigned c_pos)
  {
#ifdef DEBUG2
    std::for_each(coord.begin(), coord.end(), 
		  print< int >());
    putchar('\n');
#endif
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


  /**
   * Returns a value from 0 to 100, representing the number of cells filled with a values other than 0, which is in the form of a percentage
   */
  const unsigned CellularAutomata::progress(void) const
  {
    progress_count<Short> p;
    p = std::for_each(graph.grid.begin(), graph.grid.end(), progress_count< Short >());
    
    double percent = (((double)p.count)/((double)graph.grid.size()))*100.0;
#ifdef DEBUG
    printf("progress: %u/%u=%f%%\n", p.count, (unsigned)graph.grid.size(), percent);
#endif
    return static_cast<unsigned>(round(percent));
  }
 
} // namespace CellularAutomata


bool is_bool(bool tmp)
{
  return tmp;
}


#ifndef TESTING
int main(void)
{
  std::cout << "begin\n";
  std::vector<unsigned short> dimensions(4);
  dimensions[0] = 80;
  dimensions[1] = 45;
  dimensions[2] = 70;
  dimensions[3] = 26;
 
  std::cout << "before init graph\n";
  CellularAutomata::CellularAutomata graph(dimensions);
  std::cout << "after init graph\n";
  //int i,j,k;
  ifstream input;
  
  std::cout << "before load\n";
  input.open("data/iris_train.data");
  //input.open("points.txt");
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
		CellularAutomata::print< unsigned int >());
  putchar('\n');
  printf("Number of dimensions: %d\n", graph().get_number_dimensions());
  
  
  printf("%d%% done\n", graph.progress());
  for(unsigned steps = 0; steps < 1000 && !graph.full(); steps++) {
    graph.step();
    if(steps % 5 == 0) {
      printf("been going for %u steps\n", steps);
      printf("%d%% done\n", graph.progress());
    }
  }
  printf("finished %d%% done\n", graph.progress());
  
  
  for(int i = 0; i< 10;i++) {
    graph.step();
  }
  


  ifstream input2;
  
  std::cout << "before load\n";
  input2.open("data/iris_test.data");
  CellularAutomata::Coord coord(4);
  std::vector<bool> results;
  while(!input2.eof()) {
    short tmp = 0;
    for(unsigned i =0; i < coord.size(); i++) {
      input2 >> tmp;
      coord[i] = tmp;
    }
    input2 >> tmp;
    results.push_back(graph().get(coord) == tmp);
  }

  int number = (int) std::count_if(results.begin(), results.end(), is_bool);

  printf("passed %d / %u\n", number, (unsigned)results.size());

  return 0;
}
#endif //TESTING
