#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <map>

using namespace std;

#include "cell.hpp"

class Graph
{
public:
  Graph(void);
  Graph(Graph &orig);
  Graph(const Graph &orig);
  Graph(int width, int height);
  ~Graph(void);

  const Cell &operator () (unsigned x, unsigned y) const;
  Cell &operator () (unsigned x, unsigned y);

  const int get(int x, int y) const;
  void set(int val, int x, int y);
protected:
  vector< vector<Cell> > grid;
  unsigned width;
  unsigned height;
private:
};


#endif //GRAPH_HPP
