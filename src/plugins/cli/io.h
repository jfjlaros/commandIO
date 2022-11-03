#pragma once

#include <iostream>

using std::string;

/**
 * User input and output.
 */
class CliIO {
  public:
    CliIO(void) {}
    CliIO(int, char**);
    bool eol(void);
    void flush(void) {};
    string read(void);
    void write(string&);
    bool interactive = false;
  private:
    int _argc,
        _number = 0;
    char** _argv;
};
