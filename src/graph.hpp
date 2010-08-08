#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
//#include <list>
#include <map>
#include <set>
#include <utility> //for pair<T1, T2>
#include <istream>

using namespace std;

#include "cell.hpp"
#include "coord.hpp"

namespace CellularAutomata
{

  class Graph
  {
  public:
    friend class CellularAutomata;

    Graph(void);
    Graph(Graph &orig);
    Graph(const Graph &orig);
    Graph(const std::vector<unsigned> dimensions);
    Graph(unsigned length) :dimensions(0) {dimensions[0] = length;}
    ~Graph(void);

    const Cell &operator () (const Coord &coord) const;
    Cell &operator () (const Coord &coord);

    const int get(const Coord &coord) const;
    void set(const int val, const Coord &coord);

    const unsigned get_number_dimensions(void) const;
    const int get_dimension_size(const unsigned dimesion) const;

    const std::set<int> generate_classes(void) const;
    void load(std::istream &input);
  protected:
    /* treat as a multidimensional array
     * eg grid[x][y] == grid[size/y+x] or grid[x][y][z] == grid[size/z/y+x]
     */
    std::vector< Cell > grid;
    std::vector<unsigned> dimensions;
  private:
  };

  Graph NullGraph(0);
  
} //namespace CellularAutomata

#endif //GRAPH_HPP
