#ifndef USERIO_CLIIO_H_
#define USERIO_CLIIO_H_

#include <iostream>

using std::string;

/**
 * User input and output.
 */
class _CLiIO {
  public:
    _CLiIO(void) {}
    bool eol(void);
    void prepare(int, char**);
    string read(void);
    void write(string&);
    string output;
  private:
    int _argc,
        _number;
    char** _argv;
};

/**
 * User input and output.
 */
class CliIO {
  public:
    CliIO(int, char**);
    bool eol(void);
    void flush(void) {}
    string read(void);
    void write(string&);
    bool interactive = false;
};


extern _CLiIO _CIO;

#endif
