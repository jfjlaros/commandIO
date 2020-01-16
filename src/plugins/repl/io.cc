#include "io.h"

using std::cout;


/**
 * Check whether a line ending was encountered.
 *
 * @return `true` if a line ending was encountered, `false` otherwise.
 */
bool ReplIO::eol(void) {
  return _endOfLine;
}

/**
 * Flush the input.
 */
void ReplIO::flush(void) {
  while (!eol()) {
    read();
  }
}

/**
 * Read one string.
 *
 * @return String.
 */
string ReplIO::read(void) {
  string data = "",
         newline = "\n";
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
      write(newline);
      return "exit";
    }
  }

  _endOfLine = true;

  return data;
}

/**
 * Write one string.
 *
 * @param data String.
 */
void ReplIO::write(string& data) {
  cout << data;
}
