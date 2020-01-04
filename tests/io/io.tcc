#ifndef USERIO_IO_TCC_
#define USERIO_IO_TCC_

#include <string>

using namespace std;

/**
 * User input and output.
 */
class RWIO {
  public:
    RWIO(void) {}
    void flush(void) {}
    void write(void) {}

    void _prepare(int, char**);
    bool eol(void);
    string read(void);
    void enableCLI(int, char**),
         prepare(int, char**);
    template <class... Tail>
      void write(string&, Tail...);
    template <class... Tail>
      void write(const char*, Tail...);
    template <class H, class... Tail>
      void write(H, Tail...);
    bool interactive;
    string output;
  private:
    int _argc,
        _number;
    char** _argv;
    bool _endOfLine;
};


/**
 * Write a message.
 *
 * \param args Message.
 */
template <class... Tail>
void RWIO::write(string& data, Tail... args) {
  output += data;
  write(args...);
}

template <class... Tail>
void RWIO::write(const char* data, Tail... args) {
  output += string(data);
  write(args...);
}

template <class H, class... Tail>
void RWIO::write(H data, Tail... args) {
  output += to_string(data);
  write(args...);
}

#endif
