#ifndef USERIO_INTERFACE_TCC_
#define USERIO_INTERFACE_TCC_

/// \defgroup interface

#include "eval.tcc"
#include "help.tcc"

#define param(args...) pack(args) ///< Container for parameter definition.
#define func(args...) pack(args)  ///< Container for function definition.


/**
 * Build a user interface for one function.
 *
 * \ingroup interface
 *
 * \param io Input / output object.
 * \param f Function pointer.
 * \param name Command name.
 * \param descr Command description.
 * \param defs Parameter definitions.
 *
 * \return `true` to continue `false` to quit.
 */
template <class I, class F, class T, class... Args>
bool commandInterface(I& io, F f, T name, const char* descr, Args... defs) {
  Tuple<Args...> t = pack(defs...);

  if (!parse(io, f, t)) {
    help(io, f, name, descr, t);
  }

  return true;
}

/**
 * Build a user interface for multiple functions.
 *
 * \ingroup interface
 *
 * \param io Input / output object.
 * \param args Function definitions.
 */
template <class I, class... Args>
bool commandInterface(I& io, Args... args) {
  string command;

  if (io.interactive) {
    print(io, "> ");
  }

  if (!io.eol() || io.interactive) {
    command = io.read();
  }

  if (command == "exit") {
    return false;
  }
  if (command == "help") {
    if (io.eol() || !selectHelp(io, io.read(), args...)) {
      describe(io, args...);
    }
    return true;
  }

  if (!select(io, command, args...)) {
    describe(io, args...);
  }

  return true;
}

#endif
