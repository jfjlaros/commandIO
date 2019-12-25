#include "io.tcc"

string RWIO::_readCLI(void) {
  _number++;

  return _argv[_number];
}

string RWIO::_readREPL(void) {
  string data = "";
  bool quoted = false;
  char c = ' ';

  _endOfLine = false;

  while (c == ' ' || c == '\t') {
    c = getc(stdin);
  }

  while (c != '\n') {
    if (!quoted && (c == ' ' || c == '\t')) {
      return data;
    }
    else if (c == '\\') {
      data += getc(stdin);
    }
    else if (c == '"') {
      quoted = !quoted;
    }
    else {
      data += c;
    }

    c = getc(stdin);

    if (feof(stdin)) {
      write("\n");
      return "exit";
    }
  }

  _endOfLine = true;

  return data;
}

/**
 * Read one string.
 *
 * @return A string.
 */
string RWIO::read(void) {
  if (interactive) {
    return _readREPL();
  }
  return _readCLI();
}

/**
 * Check whether a line ending was encountered.
 *
 * @return `true` if a line ending was encountered, `false` otherwise.
 */
bool RWIO::eol(void) {
  if (interactive) {
    return _endOfLine;
  }

  return _number >= _argc - 1;
}

/**
 * Enable the command line interface (CLI) mode.
 *
 * @param argc The number of arguments in `argv`.
 * @param argv Array of arguments.
 */
void RWIO::enableCLI(int argc, char** argv) {
  interactive = false;
  _argc = argc;
  _argv = argv;
}

/**
 * Flush the input.
 */
void RWIO::flush(void) {
  while (!eol()) {
    read();
  }
}
