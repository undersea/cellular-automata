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
    bool assigned;
    Coord coord;

    Short(const Coord &coord) { this->coord = coord; bits=0; assigned=false;}
    Short(void) {bits=0; assigned=false;}

    int get(void) const { return bits; }
    void set(int val) { bits = val; assigned=bits==0?false:true;}
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
