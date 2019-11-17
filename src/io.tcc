#ifndef USERIO_IO_TCC_
#define USERIO_IO_TCC_

#include <iostream>

#define PARG_T class... Args
#define PARG Tuple<Tuple<const char*, const char*>, Args...>

using namespace std;

/**
 * User input and output.
 */
class RWIO {
  public:
    RWIO(void) {}
    bool eol(void),
         interactive(void);
    string read(void);
    void enableCLI(int, char**),
         flush(),
         write(void) {}
    template <class... Args>
      void err(Args...);
    template <class H, class... Tail>
      void write(H, Tail...);
  private:
    int _argc,
        _number = 0;
    char** _argv;
    bool _endOfLine = false,
         _interactive = true;
};

void _convert(bool*, string),
     _convert(char*, string),
     _convert(signed char*, string),
     _convert(unsigned char*, string),
     _convert(short int*, string),
     _convert(unsigned short int*, string),
     _convert(int*, string),
     _convert(unsigned int*, string),
     _convert(long int*, string),
     _convert(unsigned long int*, string),
     _convert(long long int*, string),
     _convert(unsigned long long int*, string),
     _convert(float*, string),
     _convert(double*, string),
     _convert(long double*, string),
     _convert(string*, string);


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


/**
 * Convert a string to any type.
 *
 * \param data Result of the conversion.
 * \param s Input of the conversion.
 *
 * \return `true` if the conversion was successful, `false` otherwise.
 */
template <class T>
bool convert(T* data, string s) {
  try {
    _convert(data, s);
  }
  catch (std::invalid_argument) {
    return false;
  }
  return true;
}

#endif
