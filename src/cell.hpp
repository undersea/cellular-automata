#ifndef CELL_HPP
#define CELL_HPP

enum {
  UNASSIGNED = 0
};

typedef struct
{
  char bits :7;
  Coord coord;

  Short(const Coord &coord) { this->coord = coord; }

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

#endif //CELL_HPP
