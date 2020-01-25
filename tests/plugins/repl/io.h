#ifndef USERIO_REPLIO_H_
#define USERIO_REPLIO_H_

#include <string>

using std::string;

/**
 * User input and output.
 */
class _ReplIO {
  public:
    _ReplIO(void) {}
    bool eol(void);
    void prepare(int, char**);
    string read(void);
    void write(string&);
    string output;
  private:
    int _argc,
        _number;
    char** _argv;
    bool _endOfLine;
};

/**
 * User input and output.
 */
class ReplIO {
  public:
    ReplIO(void) {}
    bool eol(void);
    void flush(void) {}
    string read(void);
    void write(string&);
    bool interactive = true;
};


extern _ReplIO _RIO;

#endif
