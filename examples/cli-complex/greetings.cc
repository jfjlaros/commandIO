/*
 * Example CLI interface for multiple functions.
 */

#include <userIO.h>


string hi(void) {
  return "Hello world.";
}

string greet(string name) {
  return "Hello " + name + ".";
}


int main(int argc, char** argv) {
  IO.enableCLI(argc, argv);

  interface(
    func(hi, "hi", "simple greeting"),
    func(greet, "greet", "personal greeting",
      param("name", "name")));

  return 0;
}
