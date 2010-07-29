#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <map>
#include <set>

using namespace std;

#include "cell.hpp"


class Graph
{
public:
  friend class CellularAutomata;

  Graph(void);
  Graph(Graph &orig);
  Graph(const Graph &orig);
  Graph(int width, int height);
  ~Graph(void);

  const Cell &operator () (unsigned x, unsigned y) const;
  Cell &operator () (unsigned x, unsigned y);

  const int get(int x, int y) const;
  void set(int val, int x, int y);

  const unsigned get_width(void) const;
  const unsigned get_height(void) const;
protected:
  vector< vector<Cell> > grid;
  unsigned width;
  unsigned height;
  std::set< int > classes;
private:
};


#endif //GRAPH_HPP
