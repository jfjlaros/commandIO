#ifndef USERIO_HELP_TCC_
#define USERIO_HELP_TCC_

/// \defgroup help

#include "io.tcc"
#include "types.tcc"
#include "tuple.tcc"

#define HELPHELP "Help on a specific command.\n"
#define EXITHELP "Exit.\n"

/**
 * Help on required parameters.
 *
 * \fn helpRequired(
 *   void (*)(H, Tail...), Tuple<Tuple<const char*, const char*>, Args...>&)
 * \ingroup help
 *
 * \param f Function pointer.
 * \param defs Parameter definitions.
 */
inline void helpRequired(void (*)(void), Tuple<>&) {}

// Required parameter.
template <class H, class... Tail, PARG_T>
void helpRequired(void (*f)(H, Tail...), PARG& defs) {
  H data;

  IO.write(
    "  ", defs.head.head, "\t\t", defs.head.tail.head, " (type ", typeof(data),
    ")\n");
  helpRequired((void (*)(Tail...))f, defs.tail);
}

// Skip optional parameter.
template <class H, class... Tail, class D>
void helpRequired(void (*f)(H, Tail...), D& defs) {
  helpRequired((void (*)(Tail...))f, defs.tail);
}


/**
 * Help on optional parameters.
 *
 * \fn helpOptional(void (*)(H, Tail...), D&) {
 * \ingroup help
 *
 * \param f Function pointer.
 * \param defs Parameter definitions.
 */
inline void helpOptional(void (*)(void), Tuple<>&) {}

// Skip required parameter.
template <class H, class... Tail, PARG_T>
void helpOptional(void (*f)(H, Tail...), PARG& defs) {
  helpOptional((void (*)(Tail...))f, defs.tail);
}

// Optional parameter of type `flag`.
template <class... Tail, class D>
void helpOptional(void (*f)(bool, Tail...), D& defs) {
  IO.write(
    "  ", defs.head.head, "\t\t", defs.head.tail.tail.head, " (type flag)\n");
  helpOptional((void (*)(Tail...))f, defs.tail);
}

// Optional parameter.
template <class H, class... Tail, class D>
void helpOptional(void (*f)(H, Tail...), D& defs) {
  H data;

  IO.write(
    "  ", defs.head.head, "\t\t", defs.head.tail.tail.head, " (type ",
    typeof(data), ", default: ", defs.head.tail.head, ")\n");
  helpOptional((void (*)(Tail...))f, defs.tail);
}


/**
 * Help on return type.
 *
 * \fn returnType(R (*)(FArgs...))
 * \ingroup help
 *
 * \param - Function pointer.
 */
template <class... FArgs>
void returnType(void (*)(FArgs...)) {}

// Entry point.
template <class R, class... FArgs>
void returnType(R (*)(FArgs...)) {
  R data;

  IO.write("\nreturns:\n  ", typeof(data), "\n");
}


/**
 * Give a full description of a command.
 *
 * \ingroup help
 *
 * \param f Function pointer.
 * \param name Command name.
 * \param descr Command description.
 * \param defs Parameter definitions.
 */
template <class R, class... FArgs, class D>
void help(R (*f)(FArgs...), string name, string descr, D& defs) {
  int req,
      opt;

  IO.write(name, ": ", descr, "\n");

  countArgs(req, opt, defs);

  if (req) {
    IO.write("\npositional arguments:\n");
    helpRequired((void (*)(FArgs...))f, defs);
  }

  if (opt) {
    IO.write("\noptional arguments:\n");
    helpOptional((void (*)(FArgs...))f, defs);
  }

  returnType(f);
}

/**
 * Give a full description of a command.
 *
 * \ingroup help
 *
 * \param m Tuple containing pointers to a class instance and a class member
 *   function.
 * \param name Command name.
 * \param descr Command description.
 * \param defs Parameter definitions.
 */
template <TMEMB_T, class D>
void help(TMEMB m, string name, string descr, D& defs) {
  help((R (*)(FArgs...))m.tail.head, name, descr, defs);
}


/**
 * Select a command for help.
 *
 * \fn selectHelp(string, H, Tail...)
 * \ingroup help
 *
 * \param name Command name.
 * \param t Function definition under consideration.
 * \param args Remaining function definitions.
 *
 * \return `true` on success, `false` otherwise.
 */
inline bool selectHelp(string name) {
  bool result = true;

  if (name == "help") {
    IO.write(
      name, ": ", HELPHELP, "\npositional arguments:\n",
      "  name\t\tcommand name (type string)\n");
  }
  else if (IO.interactive() && name == "exit") {
    IO.write(name, ": ", EXITHELP);
  }
  else {
    IO.write("Unknown command: ", name, "\n");
    result = false;
  }

  IO.flush();

  return result;
}

// Entry point.
template <class H, class... Tail>
bool selectHelp(string name, H t, Tail... args) {
  if (t.tail.head == name) {
    help(t.head, t.tail.head, t.tail.tail.head, t.tail.tail.tail);
    return true;
  }

  return selectHelp(name, args...);
}


/**
 * Short description of all available functions.
 *
 * \fn describe(Args...)
 * \ingroup help
 *
 * \param args Function definitions.
 */
inline void _describe(void) {
  IO.write("  help\t\t", HELPHELP);
  if (IO.interactive()) {
    IO.write("  exit\t\t", EXITHELP);
  }
  IO.flush();
}

// Short description of one function.
template <class H, class... Tail>
void _describe(H t, Tail... args) {
  IO.write("  ", t.tail.head, "\t\t", t.tail.tail.head, "\n");
  _describe(args...);
}

// Entry point.
template <class... Args>
void describe(Args... args) {
  IO.write("Available commands:\n");
  _describe(args...);
}

#endif
