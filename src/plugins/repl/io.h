#ifndef USERIO_REPLIO_H_
#define USERIO_REPLIO_H_

#include <iostream>

using std::string;

/**
 * User input and output.
 */
class ReplIO {
  public:
    ReplIO(void) {}
    bool eol(void);
    void flush(void);
    string read(void);
    void write(string&);
    bool interactive = true;
  private:
    bool _endOfLine = false;
};

#endif
