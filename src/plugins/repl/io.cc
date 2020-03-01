#include <fcntl.h>

#include "io.h"

using std::cout;


/**
 *
 */
ReplIO::ReplIO(void) {
  int fd = fileno(stdin);

  fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}

/**
 *
 */
void ReplIO::_store(int c) {
  if (c || _index && _data[_index - 1]) {
    _data[_index] = (char)c;
    _index++;
  }
}

/**
 * Check whether a line ending was encountered.
 *
 * @return `true` if a line ending was encountered, `false` otherwise.
 */
bool ReplIO::eol(void) {
  return !(_index || _offset);
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
 *
 */
size_t ReplIO::available(void) {
  int c = getc(stdin);

  if (c != -1) {
    if (_escape) {
      _store(c);
      _escape = false;
      return 0;
    }

    switch (c) {
      case '\\':
        _escape = true;
        break;
      case '"':
        _quoted = !_quoted;
        break;
      case ' ':
      case '\t':
        if (!_quoted) {
          _store('\0');
        }
        else {
          _store(c);
        }
        break;
      case '\n':
        _store('\0');
        _escape = false;
        _quoted = false;

        return _index;
      default:
        _store(c);
    }
  }

  return 0;
}

/**
 *
 */
char* ReplIO::read(void) {
  size_t offset = _offset;

  while (_offset < _index - 1) {
    if (!_data[_offset]) {
      _offset++;
      return &_data[offset];
    }
    _offset++;
  }

  _index = 0;
  _offset = 0;

  return &_data[offset];
}

/**
 * Write one string.
 *
 * @param data String.
 */
void ReplIO::write(string& data) {
  cout << data;
}
