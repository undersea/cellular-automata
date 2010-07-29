//#include <iostream>
#include "graph.hpp"

Graph::Graph(void)
  : grid(100, vector<Cell>(100)), width(100), height(100)
{
  //classes.insert(0);
  //classes.insert(1);
  //classes.insert(2);
}


Graph::Graph(Graph &orig)
  :grid(orig.grid), width(orig.width), height(orig.height), classes(orig.classes)
{

}


Graph::Graph(const Graph &orig)
  : grid(orig.grid), width(orig.width), height(orig.height), classes(orig.classes)
{
  
}


Graph::Graph(int width, int height)
  : grid(width, vector<Cell>(height)), width(width), height(height)
{
  classes.insert(0);
  classes.insert(1);
  classes.insert(2);
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
  for(int i = 0; i < width; i++) {
    for(int j = 0; j < height; j++) {
      classes.insert(grid[i][j].get());
    }
  }

  return classes;
}
