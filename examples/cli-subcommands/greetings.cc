/*
 * Example CLI interface for multiple functions.
 */

#include <commandIO.h>


string hi(bool shout) {
  if (shout) {
    return "HELLO WORLD!";
  }
  return "Hello world.";
}

string greet(string name) {
  return "Hello " + name + ".";
}

string flood(string name, int times) {
  string greeting = "";
  int i;

  for (i = 0; i < times; i++) {
    greeting += "Hi " + name + ".\n";
  }

  return greeting;
}


int main(int argc, char** argv) {
  CliIO io(argc, argv);

  interface(
    io,
    func(hi, "hi", "simple greeting",
      param("-s", false, "shout")),
    func(greet, "greet", "personal greeting",
      param("name", "name")), 
    func(flood, "flood", "multiple personal greetings",
      param("name", "name"),
      param("-n", 1, "multiplier")));

  return 0;
}
