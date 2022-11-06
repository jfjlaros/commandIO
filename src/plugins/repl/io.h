#pragma once

#include <iostream>

using std::string;


/**
 * User input and output.
 */
class ReplIO {
public:
  ReplIO();

  ~ReplIO();


  size_t available();

  /*!
   * Check whether a line ending was encountered.
   *
   * @return `true` if a line ending was encountered, `false` otherwise.
   */
  bool eol() const;

  /**
   * Flush the input.
   */
  void flush();
  char* read();
  void write(string const&) const;

  bool interactive {true};

private:
  void store_(int);

  char* data_ {new char[100]};
  size_t index_ {0};
  size_t offset_ {0};
  bool escape_ {false};
  bool quoted_ {false};
};
