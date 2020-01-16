#include "io.h"

using std::cout;


CliIO::CliIO(int argc, char** argv) {
  _argc = argc;
  _argv = argv;
}

/**
 * Check whether a line ending was encountered.
 *
 * @return `true` if a line ending was encountered, `false` otherwise.
 */
bool CliIO::eol(void) {
  return _number >= _argc - 1;
}

/**
 * Read one string.
 *
 * @return String.
 */
string CliIO::read(void) {
  _number++;

  return _argv[_number];
}

/**
 * Write one string.
 *
 * @param data String.
 */
void CliIO::write(string& data) {
  cout << data;
}
