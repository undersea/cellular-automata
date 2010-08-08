#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
//#include <list>
#include <map>
#include <set>
#include <istream>

using namespace std;

#include "cell.hpp"

namespace CellulaAutomata
{

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

    const std::set<int> generate_classes(void) const;
    void load(std::istream &input);
  protected:
    std::vector< std::vector<Cell> > grid;
    unsigned width;
    unsigned height;
  private:
  };

} //namespace CellulaAutomata

#endif //GRAPH_HPP
