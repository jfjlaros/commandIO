#include <commandIO.h>


class Calculator {
  public:
    Calculator(void) {}
    void add(int amount) {
      _total += amount;
    }
    void subtract(int amount) {
      _total -= amount;
    }
    int show(void) {
      return _total;
    }
  private:
    int _total = 0;
};


int main(void) {
  Calculator calc;

  while (interface(
    func(pack(&calc, &Calculator::add), "add", "Increase the total.",
      param("amount", "increase by this amount")),
    func(pack(&calc, &Calculator::subtract), "sub", "Decrease the total.",
      param("amount", "decrease by this amount")),
    func(pack(&calc, &Calculator::show), "show", "Show total.")));

  return 0;
}
