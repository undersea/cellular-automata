#include "cell.hpp"


Cell::Cell(void)
  : value()
{
  value.bits = UNASSIGNED;
}


Cell::~Cell(void)
{

}


int Cell::get(void) const
{
  return value.bits;
}


void Cell::set(int val)
{
  value.bits = val;
}
