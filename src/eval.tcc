#ifndef USERIO_EVAL_TCC_
#define USERIO_EVAL_TCC_

/**
 * @file eval.tcc
 *
 * Collect parameter values, execute a function and write the result.
 */

#include "tuple.tcc"


/**
 * Execute a function.
 *
 * All parameters have been collected since function pointer @a *f_ has no
 * parameter types. All values are now present in the @a args parameter pack.
 *
 * @param - Dummy function pointer.
 * @param f Function pointer.
 * @param args Parameter pack for @a f.
 *
 * @private
 */
template <VMEMB_T, class... Args>
void _call(void (*)(void), VMEMB m, Tuple<>&, Args&... args) {
  (*m.head.*m.tail.head)(args...);
}

/// @private Void function.
template <class... FArgs, class... Args>
void _call(void (*)(void), void (*f)(FArgs...), Tuple<>&, Args&... args) {
  f(args...);
}

/// @private Class member function.
template <TMEMB_T, class... Args>
void _call(void (*)(void), TMEMB m, Tuple<>&, Args&... args) {
  IO.write((*m.head.*m.tail.head)(args...), "\n");
}

/// @private Normal function.
template <class F, class... Args>
void _call(void (*)(void), F f, Tuple<>&, Args&... args) {
  IO.write(f(args...), "\n");
}


/**
 * Parameter collection.
 */
template <class H, class... Tail, class F, class U, class... Args>
void _call(void (*f_)(H, Tail...), F f, U& argv, Args&... args) {
  _call((void (*)(Tail...))f_, f, argv.tail, args..., argv.head);
}


/**
 * Set up parameter collection.
 */
template <TMEMB_T, class U>
void call(TMEMB m, U& argv) {
  _call((void (*)(FArgs...))m.head, m, argv);
}

/// @private Normal function.
template <class R, class... FArgs, class U>
void call(R (*f)(FArgs...), U& argv) {
  _call((void (*)(FArgs...))f, f, argv);
}


/**
 * Parse command line parameters.
 */
template <class F, class D, class A>
bool _parse(F f, D& defs, A& argv) {
  string token = "";
  int req,
      opt,
      number = 0;

  setDefault(argv, defs);

  while (!IO.eol()) {
    token = IO.read();

    if (token[0] == '-') {
      if (!updateOptional(argv, defs, token)) {
        return false;
      }
    }
    else {
      if (!updateRequired(argv, defs, number, token)) {
        return false;
      }
      number++;
    }
  }

  countArgs(req, opt, defs);

  if (number < req) {
    IO.write("Required parameter missing.\n");
    return false;
  }

  call(f, argv);

  return true;
}

template <TMEMB_T, class D>
bool parse(TMEMB m, D defs) {
  Tuple<FArgs...> argv;

  return _parse(m, defs, argv);
}

template <class R, class... FArgs, class U>
bool parse(R (*f)(FArgs...), U defs) {
  Tuple<FArgs...> argv;

  return _parse(f, defs, argv);
}


/*
 * Select a function to be executed.
 */
inline bool select(string name) {
  IO.write("Unknown command: ", name, "\n");
  IO.flush();
  return false;
}

template <class H, class... Args>
bool select(string name, H t, Args... args) {
  if (t.tail.head == name) {
    return parse(t.head, t.tail.tail.tail);
  }

  return select(name, args...);
}

#endif
