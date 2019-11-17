#include "io.tcc"


/**
 * Read one string.
 *
 * @return A string.
 */
string RWIO::read(void) {
  string data = "";
  bool quoted = false;
  char c = ' ';

  if (_interactive) {
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
  else if (!eol()) {
    _number++;
    data = _argv[_number];
  }

  return data;
}

/**
 * Check whether a line ending was encountered.
 *
 * @return `true` if a line ending was encountered, `false` otherwise.
 */
bool RWIO::eol(void) {
  if (_interactive) {
    return _endOfLine;
  }

  return _number >= _argc - 1;
}

/**
 * Check whether interactive (REPL) mode was set.
 *
 * @return `true` if interactive mode was set, `false` otherwise.
 */
bool RWIO::interactive(void) {
  return _interactive;
}

/**
 * Enable the command line interface (CLI) mode.
 *
 * @param argc The number of arguments in `argv`.
 * @param argv Array of arguments.
 */
void RWIO::enableCLI(int argc, char** argv) {
  _interactive = false;
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


/*
 * Conversion functions.
 */

void _convert(bool* data, string s) {
  *data = (bool)stoi(s);
}

void _convert(char* data, string s) {
  *data = (char)stoi(s);
}

void _convert(signed char* data, string s) {
  *data = (signed char)stoi(s);
}

void _convert(unsigned char* data, string s) {
  *data = (unsigned char)stoi(s);
}

void _convert(short int* data, string s) {
  *data = (short int)stoi(s);
}

void _convert(unsigned short int* data, string s) {
  *data = (unsigned short int)stoi(s);
}

void _convert(int* data, string s) {
  *data = stoi(s);
}

void _convert(unsigned int* data, string s) {
  *data = (unsigned int)stoi(s);
}

void _convert(long int* data, string s) {
  *data = stol(s);
}

void _convert(unsigned long int* data, string s) {
  *data = stoul(s);
}

void _convert(long long int* data, string s) {
  *data = stoll(s);
}

void _convert(unsigned long long int* data, string s) {
  *data = stoull(s);
}

void _convert(float* data, string s) {
  *data = stof(s);
}

void _convert(double* data, string s) {
  *data = stod(s);
}

void _convert(long double* data, string s) {
  *data = stold(s);
}

void _convert(string* data, string s) {
  *data = s;
}
