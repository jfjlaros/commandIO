#ifndef USERIO_CLIIO_H_
#define USERIO_CLIIO_H_

#include <iostream>

using namespace std;

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

#endif
