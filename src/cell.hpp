#ifndef CELL_HPP
#define CELL_HPP

#include "coord.hpp"

namespace CellularAutomata
{

  enum {
    UNASSIGNED = 0
  };

  typedef struct Short
  {
    char bits :7;
    Coord coord;

    Short(const Coord &coord) { this->coord = coord; }
    Short(void) {}

    int get(void) const { return bits; }
    void set(int val) { bits = val; }
  } Short;


  class Cell
  {
  public:
    Cell(void);
    ~Cell(void);

    int get(void) const;
    void set(int val);
  protected:
    char bits :7;
  private:
  };
} // CellularAutomata
#endif //CELL_HPP
