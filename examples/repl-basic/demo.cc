#include <commandIO.h>


string greet(string name, int times, bool shout) {
  string greeting = "";
  int i;

  for (i = 0; i < times; i++) {
    if (shout) {
      greeting += "HI " + name + "!\n";
    }
    else {
      greeting += "Hi " + name + ".\n";
    }
  }

  return greeting;
}

int increase(int a) {
  return a + 1;
}

float multiply(float a, int b) {
  return a * b;
}


int main(void) {
  ReplIO io;

  while (interface(
    io,
    func(greet, "greet", "Say hi to someone.",
      param("name", "someone's name"),
      param("-t", 1, "greet multiple times"),
      param("-s", false, "shout")),
    func(increase, "inc", "Increment a value.",
      param("value", "value to be incremented")),
    func(multiply, "mul", "Multiply a floating point number.",
      param("-a", 1.1F, "value to be multiplied"),
      param("b", "multiplier"))));

  return 0;
}
