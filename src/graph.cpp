#include <iostream>


#include <stdlib.h>

#include "graph.hpp"

namespace CellularAutomata
{
  Graph::Graph(void)
    : grid(10000), dimensions(100, 100)
  {
    std::cout << dimensions[0] << "x" << dimensions[1] << endl;
  }


  Graph::Graph(Graph &orig)
    :grid(orig.grid),
     dimensions(orig.dimensions)
  {

  }


  Graph::Graph(const Graph &orig)
    : grid(orig.grid), dimensions(orig.dimensions)
  {
  
  }


  Graph::Graph(const std::vector<unsigned> dimensions)
    : grid(), dimensions(dimensions)
  {
    unsigned size = 1;
    for(unsigned i = 0; i < this->dimensions.size(); i++) {
      size *= this->dimensions[i];
    }
    grid.resize(size);
  }


  Graph::~Graph(void)
  {
  
  }


  const Cell &Graph::operator () (const Coord &coord) const
  {
    unsigned pos = 0;
    unsigned i;
    for(i = 0; i < coord.size() - 1; i++) {
      pos += coord[i] * dimensions[i];
    }

    pos += coord[i];

    return grid[pos];
  }

  
  Cell &Graph::operator () (const Coord &coord)
  {
    unsigned pos = 0;
    unsigned i;
    for(i = 0; i < coord.size() - 1; i++) {
      pos += coord[i] * dimensions[i];
    }

    pos += coord[i];

    return grid[pos];
  }

  /*|0|1|2| |9 |10|11| |18|19|20|
   *|3|4|5| |12|13|14| |21|22|23|
   *|6|7|8| |15|16|17| |24|25|26|
   */

  
  const int Graph::get(const Coord &coord) const
  {
    return (*this)(coord).get();
  }

  void Graph::set(const int val, const Coord &coord)
  {
    (*this)(coord).set(val);
  }


  const std::set<int> Graph::generate_classes(void) const
  {
    std::set<int> classes;
    for(unsigned i = 0; i < grid.size(); i++) {
      classes.insert(grid[i].get());
    }
    

    return classes;
  }

  void Graph::load(std::istream &input, char delimeter)
  {
    while(!input.eof()) {
      unsigned axis, value;
      Coord coord(dimensions.size());
      std::cout << coord.size() << std::endl;
      for(unsigned i = 0; !input.eof() && i < dimensions.size(); i++) {
	input >> axis; //assume all data is in integer format
	std::cout << axis << ',';
	coord[i] = axis;
	
	if(delimeter != ' ') {
	  char tmp;
	  input >> tmp;
	}
	
      }
      input >> value;
      std::cout << value << std::endl;
      (*this)(coord).set(value);
    }
  }

}
