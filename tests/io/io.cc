#include "io.tcc"

/**
 * Read one string.
 *
 * @return A string.
 */
string RWIO::read(void) {
  string s;
  int i;

  _number++;

  if (interactive) {
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
  }

  return _argv[_number];
}

/**
 * Check whether a line ending was encountered.
 *
 * @return `true` if a line ending was encountered, `false` otherwise.
 */
bool RWIO::eol(void) {
  return _endOfLine || _number >= _argc - 1;
}

/**
 * Prepare data.
 *
 * @param argc The number of arguments in `argv`.
 * @param argv Array of arguments.
 */
void RWIO::_prepare(int argc, char** argv) {
  output = "";
  _argc = argc;
  _argv = argv;
  _endOfLine = false;
}

/**
 * Enable the command line interface (CLI) mode.
 *
 * @param argc The number of arguments in `argv`.
 * @param argv Array of arguments.
 */
void RWIO::enableCLI(int argc, char** argv) {
  _prepare(argc, argv);
  interactive = false;
  _number = 0;
}

/**
 * Prepare data for the REPL mode.
 *
 * @param argc The number of arguments in `argv`.
 * @param argv Array of arguments.
 */
void RWIO::prepare(int argc, char** argv) {
  _prepare(argc, argv);
  interactive = true;
  _number = -1;
}
