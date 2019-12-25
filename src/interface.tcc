#ifndef USERIO_INTERFACE_TCC_
#define USERIO_INTERFACE_TCC_

/// \defgroup interface

#include "args.tcc"
#include "eval.tcc"
#include "help.tcc"

#define param(args...) pack(args) ///< Container for parameter definition.
#define func(args...) pack(args)  ///< Container for function definition.

RWIO IO;                          ///< User input and output.



/**
 * Build a user interface for one function.
 *
 * \ingroup interface
 *
 * \param f Function pointer.
 * \param name Command name.
 * \param descr Command description.
 * \param defs Parameter definitions.
 *
 * \return `true` to continue `false` to quit.
 */
template <class F, class T, class... Args>
bool interface(F f, T name, const char* descr, Args... defs) {
  Tuple<Args...> t = pack(defs...);

  if (!parse(f, t)) {
    help(f, name, descr, t);
  }

  return true;
}

/**
 * Build a user interface for multiple functions.
 *
 * \ingroup interface
 *
 * \param args Function definitions.
 */
template <class... Args>
bool interface(Args... args) {
  string command;

  if (IO.interactive) {
    IO.write("> ");
  }

  if (!IO.eol() || IO.interactive) {
    command = IO.read();
  }

  if (command == "exit") {
    return false;
  }
  if (command == "help") {
    if (IO.eol() || !selectHelp(IO.read(), args...)) {
      describe(args...);
    }
    return true;
  }

  if (!select(command, args...)) {
    describe(args...);
  }

  return true;
}

#endif
