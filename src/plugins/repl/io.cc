#include <fcntl.h>

#include "io.h"

using std::cout;


ReplIO::ReplIO() {
  int fd {fileno(stdin)};
  fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}

ReplIO::~ReplIO() {
  delete[] data_;
}


size_t ReplIO::available() {
  int c {getc(stdin)};

  if (c != -1) {
    if (escape_) {
      store_(c);
      escape_ = false;
      return 0;
    }

    switch (c) {
      case '\\':
        escape_ = true;
        break;
      case '"':
        quoted_ = not quoted_;
        break;
      case ' ':
      case '\t':
        if (not quoted_) {
          store_('\0');
        }
        else {
          store_(c);
        }
        break;
      case '\n':
        store_('\0');
        escape_ = false;
        quoted_ = false;

        return index_;
      default:
        store_(c);
    }
  }

  return 0;
}

bool ReplIO::eol() const {
  return not (index_ or offset_);
}

void ReplIO::flush() {
  while (not eol()) {
    read();
  }
}

char* ReplIO::read() {
  size_t offset {offset_};

  while (offset_ < index_ - 1) {
    if (not data_[offset_]) {
      offset_++;
      return &data_[offset];
    }
    offset_++;
  }

  index_ = 0;
  offset_ = 0;

  return &data_[offset];
}

void ReplIO::write(string const& data) const {
  cout << data;
}


void ReplIO::store_(int c) {
  if (c or (index_ and data_[index_ - 1])) {
    data_[index_] = (char)c;
    index_++;
  }
}
