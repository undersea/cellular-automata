#include "cell.hpp"


namespace CellularAutomata
{

Cell::Cell(void)
  : bits(UNASSIGNED)
{

}


Cell::~Cell(void)
{

}


int Cell::get(void) const
{
  return bits;
}


void Cell::set(int val)
{
  bits = val;
}

} //CellularAutomata
