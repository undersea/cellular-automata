#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <map>

#include "cell.hpp"

class Graph
{
public:
  Graph(void);
  Graph(int width, int height);
  ~Graph(void);

  const int &operator () (unsigned x, unsigned y) const;
  int &operator () (unsigned x, unsigned y);

  const int get(int x, int y) const;
  void set(int val, int x, int y);
protected:
  vector<vector<Cell>> grid;
  vector<vector<Cell>> scratch;
private:
};


#endif //GRAPH_HPP
