#include <catch.hpp>

#include "plugins/cli/io.h"

#define __call__(f, argv) f(sizeof(argv) / sizeof(const char*), (char**)argv)

#define main __doc_main__
#include "../examples/doc/doc.cc"
#undef main

#define main __cli_single_main__
#include "../examples/cli-single/sequence.cc"
#undef main


TEST_CASE("Documentation test", "[example]") {
  const char* argv[] = {"dummy", "8", "9"};

  __call__(__doc_main__, argv);
  //REQUIRE(_CIO.output == "17\n");
}

/*
TEST_CASE("CLI test", "[example]") {
  const char* argv0[] = {"dummy", "11"};
  const char* argv1[] = {"dummy", "11", "-a", "3"};

  __call__(__cli_single_main__, argv0);
  REQUIRE(_CIO.output == "89\n");
  
  __call__(__cli_single_main__, argv1);
  REQUIRE(_CIO.output == "254\n");
}
*/
