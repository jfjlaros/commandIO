#ifndef USERIO_REPLIO_H_
#define USERIO_REPLIO_H_

#include <iostream>

using std::string;

/**
 * User input and output.
 */
class ReplIO {
  public:
    ReplIO(void);
    size_t available(void);
    bool eol(void);
    void flush(void);
    char* read(void);
    void write(string&);
    bool interactive = true;
  private:
    void _store(int);
    char* _data = (char*)malloc(100 * sizeof(char));
    size_t _index = 0,
           _offset = 0;
    bool _escape = false,
         _quoted = false;
};

#endif
