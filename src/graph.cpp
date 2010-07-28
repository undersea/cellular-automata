#include "graph.hpp"

Graph::Graph(void)
{
  grid = new Cell[100][100];
}

Graph::Graph(int width, int height)
{

}


Graph::~Graph(void)
{

}


const int &Graph::operator () (unsigned x, unsigned y) const
{
  return grid[x][y];
}


int Graph::


const int Graph::get(int x, int y) const
{
  return -1;
}

void Graph::set(int val, int x, int y)
{

}
