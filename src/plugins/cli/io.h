#pragma once

#include <iostream>

using std::string;


/*!
 * User input and output.
 */
class CliIO {
public:
  CliIO() {}

  CliIO(int, char**);

  /*!
   * Check whether a line ending was encountered.
   *
   * \return `true` if a line ending was encountered, `false` otherwise.
   */
  bool eol() const;

  void flush() {};

  /*!
   * Read one string.
   *
   * \return String.
   */
  string read();

  /*!
   * Write one string.
   *
   * \param[in] data String.
   */
  void write(string const&) const;

  bool interactive {false};

private:
  int argc_;
  char** argv_;
  int number_ {0};
};
