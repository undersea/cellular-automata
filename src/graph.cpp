#include <iostream>

#include <algorithm>

#include <cstdlib>
#include <cstdio>

//#define DEBUG

#include "graph.hpp"

namespace CellularAutomata
{
  template<class U> struct multiple_total : public unary_function<U, void>
  {
    multiple_total(void) : total(1){}
    void operator () (U x) { 
      total*=x;
    }
    unsigned total;
  };

  Graph::Graph(void)
    : grid(10000), dimensions(100, 100)
  {
    std::cout << dimensions[0] << "x" << dimensions[1] << std::endl;
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


  Graph::Graph(const std::vector<unsigned short> dimensions)
    : grid(), dimensions(dimensions)
  {
    unsigned size = 1;
    for(unsigned i = 0; i < this->dimensions.size(); i++) {
      size *= this->dimensions[i];
    }
    grid.resize(size);
    std::cout << "graph size = " << size << std::endl;
  }


  Graph::~Graph(void)
  {
  
  }


  const Short &Graph::operator () (const Coord &coord) const
  {
    //first get the x,y pos
    unsigned pos = coord[0] + coord[1] * dimensions[0];
    unsigned multiple = dimensions[0]*dimensions[1];
    if(coord.size() > 2 && dimensions.size() > 2) {
      for(unsigned i = 2; i < coord.size(); i++) {
	pos += coord[i] * multiple;
	multiple *= dimensions[i];
      }
    }
#ifdef DEBUG
    printf("pos = %u\n", pos);
#endif
    return grid[pos];
  }

  
  
  Short &Graph::operator () (const Coord &coord)
  {
    //first get the x,y pos
    unsigned pos = coord[0] + coord[1] * dimensions[0];
    unsigned multiple = dimensions[0]*dimensions[1];
    if(coord.size() > 2 && dimensions.size() > 2) {
      for(unsigned i = 2; i < coord.size(); i++) {
	pos += coord[i] * multiple;
	multiple *= dimensions[i];
      }
    }
#ifdef DEBUG
    printf("pos = %u\n", pos);
#endif
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


  const std::set<unsigned> Graph::generate_classes(void) const
  {
    /*std::set<int> classes;
    for(unsigned i = 0; i < grid.size(); i++) {
      classes.insert(grid[i].get());
    }
    

    return classes;*/
    return klasses;
  }

  void Graph::load(std::istream &input, char delimeter)
  {
    while(!input.eof()) {
      unsigned axis, value;
      Coord coord(dimensions.size());
      for(unsigned i = 0; !input.eof() && i < dimensions.size(); i++) {
	input >> axis; //assume all data is in integer format
	coord[i] = axis;
	
	if(delimeter != ' ') {
	  char tmp;
	  input >> tmp;
	}
	
      }
      input >> value;
      //Short val;
      //val.bits = value;
      this->klasses.insert(value);
      (*this)(coord).set(value);
    }
  }
  
  const unsigned Graph::get_number_dimensions(void) const
  {
    return dimensions.size();
  }


  const std::vector< Short > Graph::get_grid(void) const
  {
    return grid;
  }
}
