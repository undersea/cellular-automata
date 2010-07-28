#include "cell.hpp"


Cell::Cell(void)
  : value(UNASSIGNED)
{

}


Cell::~Cell(void)
{

}


int Cell::get(void) const
{
  return value;
}


void Cell::set(int val)
{
  value = val;
}
