#ifndef CELLULAR_AUTOMATA
#define CELLULAR_AUTOMATA

class CellularAutomata
{
public:
  CellularAutomata(void);
  CellularAutomata(unsigned width, unsigned height);
  ~CellularAutomata(void);

  void init(unsigned width, unsigned height);
  void step(void);
  

  Graph get(void) const;
  void set(Graph &grid);

protected:
  void calculate(unsigned x, unsigned y);
  
  Graph graph;
  Graph graph2;
private:
};

#endif //CELLULAR_AUTOMATA
