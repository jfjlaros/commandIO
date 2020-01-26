#include <catch.hpp>

#include "plugins/repl/io.h"

#define main __repl_class_main__
#include "../examples/repl-class/calculator.cc"
#undef main


TEST_CASE("Class test", "[example]") {
  const char* argv[] = {"add", "6\n", "show"};

  _RIO.prepare(3, (char**)argv);

  __repl_class_main__();

  REQUIRE(_RIO.output == "> > 6\n> ");
}
