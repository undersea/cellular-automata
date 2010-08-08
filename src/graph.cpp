//#include <iostream>
#include "graph.hpp"

namespace CellulaAutomata
{

  Graph::Graph(void)
    : grid(100, std::vector<Cell>(100)), width(100), height(100)
  {

  }


  Graph::Graph(Graph &orig)
    :grid(orig.grid), width(orig.width), height(orig.height)
  {

  }


  Graph::Graph(const Graph &orig)
    : grid(orig.grid), width(orig.width), height(orig.height)
  {
  
  }


  Graph::Graph(int width, int height)
    : grid(width, std::vector<Cell>(height)), width(width), height(height)
  {

  }


  Graph::~Graph(void)
  {
  
  }


  const Cell &Graph::operator () (unsigned x, unsigned y) const
  {
    return grid[x][y];
  }


  Cell &Graph::operator () (unsigned x, unsigned y)
  {
    return grid[x][y];
  }


  const int Graph::get(int x, int y) const
  {
  
    return grid[x][y].get();
  }

  void Graph::set(int val, int x, int y)
  {
    grid[x][y].set(val);
  }


  const unsigned Graph::get_width(void) const
  {
    return width;
  }

  const unsigned Graph::get_height(void) const
  {
    return height;
  }


  const std::set<int> Graph::generate_classes(void) const
  {
    std::set<int> classes;
    for(unsigned i = 0; i < width; i++) {
      for(unsigned j = 0; j < height; j++) {
	classes.insert(grid[i][j].get());
      }
    }

    return classes;
  }

  void Graph::load(std::istream &input)
  {
    while(!input.eof()) {
      unsigned x, y, value;
      input >> x >> y >> value;
      (*this)(x,y).set(value);
    }
  }

}
