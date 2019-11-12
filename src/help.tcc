#ifndef SIMPLE_REPL_HELP_TCC_
#define SIMPLE_REPL_HELP_TCC_

#include "io.tcc"
#include "types.tcc"
#include "tuple.tcc"

#define HELPHELP "Help on a specific command.\n"
#define EXITHELP "Exit.\n"


/*
 * Help on required parameters.
 */
inline void _helpRequired(void (*)(void), Tuple<>&) {}

template <class H, class... Tail, PARG_T>
void _helpRequired(void (*f)(H, Tail...), PARG& defs) {
  H data;

  IO.write(
    "  ", defs.head.head, "\t\t", defs.head.tail.head, " (type ",
    _typeof(data), ")\n");
  _helpRequired((void (*)(Tail...))f, defs.tail);
}

template <class H, class... Tail, class D>
void _helpRequired(void (*f)(H, Tail...), D& defs) {
  _helpRequired((void (*)(Tail...))f, defs.tail);
}


/*
 * Help on optional parameters.
 */
inline void _helpOptional(void (*)(void), Tuple<>&) {}

template <class H, class... Tail, PARG_T>
void _helpOptional(void (*f)(H, Tail...), PARG& defs) {
  _helpOptional((void (*)(Tail...))f, defs.tail);
}

template <class... Tail, class D>
void _helpOptional(void (*f)(bool, Tail...), D& defs) {
  IO.write(
    "  ", defs.head.head, "\t\t", defs.head.tail.tail.head, " (type flag)\n");
  _helpOptional((void (*)(Tail...))f, defs.tail);
}

template <class H, class... Tail, class D>
void _helpOptional(void (*f)(H, Tail...), D& defs) {
  H data;

  IO.write(
    "  ", defs.head.head, "\t\t", defs.head.tail.tail.head, " (type ",
    _typeof(data), ", default: ", defs.head.tail.head, ")\n");
  _helpOptional((void (*)(Tail...))f, defs.tail);
}


/*
 * Help on return type.
 */
template <class... FArgs>
void returnType(void (*)(FArgs...)) {}

template <class R, class... FArgs>
void returnType(R (*)(FArgs...)) {
  R data;

  IO.write("\nreturns:\n  ", _typeof(data), "\n");
}


/*
 * Help.
 */
template <class R, class... FArgs, class D>
void help(R (*f)(FArgs...), string name, string descr, D& defs) {
  int req,
      opt;

  IO.write(name, ": ", descr, "\n");

  countArgs(req, opt, defs);

  if (req) {
    IO.write("\npositional arguments:\n");
    _helpRequired((void (*)(FArgs...))f, defs);
  }

  if (opt) {
    IO.write("\noptional arguments:\n");
    _helpOptional((void (*)(FArgs...))f, defs);
  }

  returnType(f);
}

template <TMEMB_T, class D>
void help(TMEMB m, string name, string descr, D& defs) {
  help((R (*)(FArgs...))m.tail.head, name, descr, defs);
}


/*
 * Help selector.
 */
inline bool selectHelp(string name) {
  bool result = true;

  if (name == "help") {
    IO.write(
      name, ": ", HELPHELP, "\npositional arguments:\n",
      "  name\t\tcommand name (type string)\n");
  }
  else if (name == "exit") {
    IO.write(name, ": ", EXITHELP);
  }
  else {
    IO.write("Unknown command: ", name, "\n");
    result = false;
  }

  IO.flush();

  return result;
}

template <class H, class... Tail>
bool selectHelp(string name, H t, Tail... args) {
  if (t.tail.head == name) {
    help(t.head, t.tail.head, t.tail.tail.head, t.tail.tail.tail);
    return true;
  }

  return selectHelp(name, args...);
}


/*
 * Short description of all available functions.
 */
inline void _describe(void) {
  IO.write("  help\t\t", HELPHELP, "  exit\t\t", EXITHELP);
  IO.flush();
}

template <class H, class... Tail>
void _describe(H t, Tail... args) {
  IO.write("  ", t.tail.head, "\t\t", t.tail.tail.head, "\n");
  _describe(args...);
}

template <class... Args>
void describe(Args... args) {
  IO.write("Available commands:\n");
  _describe(args...);
}

#endif
