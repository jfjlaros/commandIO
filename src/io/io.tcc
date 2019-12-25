#ifndef USERIO_IO_TCC_
#define USERIO_IO_TCC_

#include <iostream>

using namespace std;

/**
 * User input and output.
 */
class RWIO {
  public:
    RWIO(void) {}
    bool eol(void);
    string read(void);
    void enableCLI(int, char**),
         flush(),
         write(void) {}
    template <class... Args>
      void err(Args...);
    template <class H, class... Tail>
      void write(H, Tail...);
    bool interactive = true;
  private:
    string _readCLI(void),
           _readREPL(void);
    int _argc,
        _number = 0;
    char** _argv;
    bool _endOfLine = false;
};


/**
 * Write an error message and flush the input.
 *
 * \param args Message.
 */
template <class... Args>
void RWIO::err(Args... args) {
  write(args...);
  flush();
}

/**
 * Write a message.
 *
 * \param args Message.
 */
template <class H, class... Tail>
void RWIO::write(H data, Tail... args) {
  cout << data;
  write(args...);
}

#endif
