#ifndef SIMPLE_REPL_HELP_TCC_
#define SIMPLE_REPL_HELP_TCC_

#include "io.tcc"
#include "types.tcc"
#include "tuple.tcc"

#define PARG Tuple<const char*, const char*>


/*
 * Help on required parameters.
 */
void _helpRequired(void (*)(void), Tuple<>&) {}

template <class T, class... Tail, class... Args>
void _helpRequired(void (*f)(T, Tail...), Tuple<PARG, Args...>& argv) {
  T data;

  IO.write(
    "  ", argv.head.head, "\t\t", argv.head.tail.head, " (type ",
    _typeof(data), ")\n");
  _helpRequired((void (*)(Tail...))f, argv.tail);
}

template <class T, class... Tail, class U>
void _helpRequired(void (*f)(T, Tail...), U& argv) {
  _helpRequired((void (*)(Tail...))f, argv.tail);
}


/*
 * Help on optional parameters.
 */
void _helpOptional(void (*)(void), Tuple<>&) {}

template <class T, class... Tail, class... Args>
void _helpOptional(void (*f)(T, Tail...), Tuple<PARG, Args...>& argv) {
  _helpOptional((void (*)(Tail...))f, argv.tail);
}

template <class... Tail, class U>
void _helpOptional(void (*f)(bool, Tail...), U& argv) {
  IO.write(
    "  ", argv.head.head, "\t\t", argv.head.tail.tail.head, " (type flag)\n");
  _helpOptional((void (*)(Tail...))f, argv.tail);
}

template <class T, class... Tail, class U>
void _helpOptional(void (*f)(T, Tail...), U& argv) {
  T data;

  IO.write(
    "  ", argv.head.head, "\t\t", argv.head.tail.tail.head, " (type ",
    _typeof(data), ", default: ", argv.head.tail.head, ")\n");
  _helpOptional((void (*)(Tail...))f, argv.tail);
}


/*
 * Help on return type.
 */
template <class... Tail>
void returnType(void (*)(Tail...)) {}

template <class T, class... Tail>
void returnType(T (*)(Tail...)) {
  T data;

  IO.write("\nreturns:\n  ", _typeof(data), "\n");
}


/*
 * Help.
 */
template <class T, class... Tail, class U>
void help(T (*f)(Tail...), string name, string descr, U argv) { // U&
  IO.write(name, ": ", descr, "\n\n");

  IO.write("positional arguments:\n");
  _helpRequired((void (*)(Tail...))f, argv);

  IO.write("\noptional arguments:\n");
  _helpOptional((void (*)(Tail...))f, argv);

  returnType(f);
}

#endif