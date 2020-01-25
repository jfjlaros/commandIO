#include <catch.hpp>

#include "plugins/cli/io.h"

#define main __doc_main__
#include "../examples/doc/doc.cc"
#undef main

/*
#define main __repl_class_main__
#include "../examples/repl-class/calculator.cc"
#undef main
*/


TEST_CASE("Documentation test", "[example]") {
  const char* argv[] = {"dummy", "8", "9"};

  __doc_main__(3, (char**)argv);

  REQUIRE(_CIO.output == "17\n");
}

/*
TEST_CASE("Class test", "[example]") {
  const char* argv[] = {
    "add", "6\n", "show"};

  _RIO.prepare(3, (char**)argv);

  __repl_class_main__();

  REQUIRE(RIO.output == "> > 6\n> ");
}
*/
