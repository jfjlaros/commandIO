#include "io.h"

/**
 * Check whether a line ending was encountered.
 *
 * @return `true` if a line ending was encountered, `false` otherwise.
 */
bool _ReplIO::eol(void) {
  return _endOfLine || _number >= _argc - 1; // || needed?
}

/**
 * Prepare data.
 *
 * @param argc The number of arguments in `argv`.
 * @param argv Array of arguments.
 */
void _ReplIO::prepare(int argc, char** argv) {
  _argc = argc;
  _argv = argv;
  _endOfLine = false;
  _number = -1;
  output = "";
}

/**
 * Read one string.
 *
 * @return A string.
 */
string _ReplIO::read(void) {
  string s;
  int i;

  _number++;

  if (_number > _argc - 1) {
    return "exit";
  }

  s = _argv[_number];
  i = s.size() - 1;

  _endOfLine = false;

  if (s[i] == '\n') {
    _endOfLine = true;
    return s.substr(0, i);
  }

  return _argv[_number];
}

/*
 *
 */
void _ReplIO::write(string& data) {
  output += data;
}


/**
 * Check whether a line ending was encountered.
 *
 * @return `true` if a line ending was encountered, `false` otherwise.
 */
bool ReplIO::eol(void) {
  return _RIO.eol();
}

/**
 * Read one string.
 *
 * @return String.
 */
string ReplIO::read(void) {
  return _RIO.read();
}

/**
 * Write one string.
 *
 * @param data String.
 */
void ReplIO::write(string& data) {
  _RIO.write(data);
}


_ReplIO _RIO;
