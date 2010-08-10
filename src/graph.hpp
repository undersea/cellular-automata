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
    Graph(const std::vector<unsigned short> dimensions);
    Graph(unsigned short length) :dimensions(0) {dimensions[0] = length;}
    ~Graph(void);

    const Short &operator () (const Coord &coord) const;
    Short &operator () (const Coord &coord);

    const int get(const Coord &coord) const;
    void set(const int val, const Coord &coord);

    const unsigned get_number_dimensions(void) const;
    const int get_dimension_size(const unsigned dimesion) const;

    const std::set<unsigned> generate_classes(void) const;
    void load(std::istream &input, char delimeter=',');
  protected:
    /* treat as a multidimensional array
     * eg grid[x][y] == grid[size/y+x] or grid[x][y][z] == grid[size/z/y+x]
     */
    std::vector< Short > grid;
    std::vector<unsigned short> dimensions;
    std::set<unsigned> klasses;
  private:
  };
  
} //namespace CellularAutomata

#endif //GRAPH_HPP
