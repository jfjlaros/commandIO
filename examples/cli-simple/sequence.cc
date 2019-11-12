/*
 * Example CLI interface for one function.
 */

#include <simpleREPL.h>


int sequence(int a, int b, int n) {
  if (n == 0)
    return a;
  if (n == 1)
    return b;
  return sequence(a, b, n - 1) + sequence(a, b, n - 2);
}


int main(int argc, char** argv) {
  IO.enableCLI(argc, argv);

  interface(
    sequence, argv[0], "Give the n-th number in a sequence.", 
      param("-a", 0, "first number"),
      param("-b", 1, "second number"),
      param("n", "desired number in the sequence"));

  return 0;
}
