#ifndef CELLULAR_AUTOMATA
#define CELLULAR_AUTOMATA

template<class T> struct find_best : public unary_function<T, void>
{
  void operator() (T x){
    even &= total == x.second;
    best_value = x.second > total && x.first != 0 ? x.first : best_value;
    total = best_value == x.first && x.first != 0 ? x.second : total;
  }
  int best_value;
  int total;
  bool even;
};

namespace CellulaAutomata
{

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

  Graph &operator () (void);
protected:
  void calculate(unsigned x, unsigned y);
  
  Graph graph;
  Graph graph2;
private:
};

}
#endif //CELLULAR_AUTOMATA
