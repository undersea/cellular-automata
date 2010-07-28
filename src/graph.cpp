#include "graph.hpp"

Graph::Graph(void)
  : grid(100, vector<Cell>(100))
{
 
}


Graph::Graph(Graph &orig)
  :grid(orig.grid)
{

}


Graph::Graph(const Graph &orig)
  :grid(orig.grid)
{

}


Graph::Graph(int width, int height)
  : grid(width, vector<Cell>(height))
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
