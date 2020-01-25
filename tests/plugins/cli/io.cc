#include "io.h"

/**
 * Check whether a line ending was encountered.
 *
 * @return `true` if a line ending was encountered, `false` otherwise.
 */
bool _CLiIO::eol(void) {
  return _number >= _argc - 1;
}

/**
 * Prepare data.
 *
 * @param argc The number of arguments in `argv`.
 * @param argv Array of arguments.
 */
void _CLiIO::prepare(int argc, char** argv) {
  output = "";
  _argc = argc;
  _argv = argv;
}

/**
 * Read one string.
 *
 * @return A string.
 */
string _CLiIO::read(void) {
  _number++;

  return _argv[_number];
}

/**
 *
 */
void _CLiIO::write(string& data) {
  output += data;
}


/**
 *
 */
CliIO::CliIO(int argc, char** argv) {
  _CIO.prepare(argc, argv);
}

/**
 * Check whether a line ending was encountered.
 *
 * @return `true` if a line ending was encountered, `false` otherwise.
 */
bool CliIO::eol(void) {
  return _CIO.eol();
}

/**
 * Read one string.
 *
 * @return String.
 */
string CliIO::read(void) {
  return _CIO.read();
}

/**
 * Write one string.
 *
 * @param data String.
 */
void CliIO::write(string& data) {
  _CIO.write(data);
}


_CLiIO _CIO;
