#include <catch.hpp>

#define main __test_doc__
#include "../examples/doc/doc.cc"
#undef main

#define main __test_repl_class__
#include "../examples/repl-class/calculator.cc"
#undef main


TEST_CASE("Documentation test", "[example]") {
  const char* argv[] = {"dummy", "8", "9"};

  __test_doc__(3, (char**)argv);

  REQUIRE(IO.output == "17\n");
}

TEST_CASE("Class test", "[example]") {
  const char* argv[] = {
    "add", "6\n", "show"};

  IO.prepare(3, (char**)argv);

  __test_repl_class__();

  REQUIRE(IO.output == "> > 6\n> ");
}
