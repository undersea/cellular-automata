#ifndef CELL_HPP
#define CELL_HPP

enum {
  UNASSIGNED = -1
};

class Cell
{
public:
  Cell(void);
  ~Cell(void);

  int get(void) const;
  void set(int val);
protected:
  int value;
private:
};

#endif //CELL_HPP
