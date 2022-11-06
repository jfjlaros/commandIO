#include "io.h"

using std::cout;


CliIO::CliIO(int argc, char** argv) {
  argc_ = argc;
  argv_ = argv;
}

bool CliIO::eol() const {
  return number_ >= argc_ - 1;
}

string CliIO::read() {
  return argv_[++number_];
}

void CliIO::write(string const& data) const {
  cout << data;
}
