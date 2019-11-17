#ifndef USERIO_EVAL_TCC_
#define USERIO_EVAL_TCC_

/// \defgroup eval

#include "tuple.tcc"


/*
 * Recursion terminators.
 *
 * All parameters have been collected. All values are now present in the `args`
 * parameter pack.
 */

// Void class member function.
template <VMEMB_T, class... Args>
void _call(VMEMB& m, Tuple<>&, Args&... args) {
  (*m.head.*m.tail.head)(args...);
}

// Void function.
template <class... FArgs, class... Args>
void _call(void (*f)(FArgs...), Tuple<>&, Args&... args) {
  f(args...);
}

// Class member function that returns a value.
template <TMEMB_T, class... Args>
void _call(TMEMB& m, Tuple<>&, Args&... args) {
  IO.write((*m.head.*m.tail.head)(args...), "\n");
}

// Function that returns a value.
template <class F, class... Args>
void _call(F f, Tuple<>&, Args&... args) {
  IO.write(f(args...), "\n");
}


/*
 * Parameter collection.
 *
 * The first member of the tuple `argv` is added to the parameter pack `args`.
 */
template <class F, class A, class... Args>
void _call(F f, A& argv, Args&... args) {
  _call(f, argv.tail, args..., argv.head);
}


/**
 * Call a class member function.
 *
 * \ingroup eval
 *
 * \param m Tuple containing pointers to a class instance and a class member
 *   function.
 * \param argv Tuple containing arguments.
 */
template <TMEMB_T, class A>
void call(TMEMB& m, A& argv) {
  _call(m, argv);
}

/**
 * Call a function.
 *
 * \ingroup eval
 *
 * \param f Function pointer.
 * \param argv Tuple containing arguments.
 */
template <class F, class A>
void call(F f, A& argv) {
  _call(f, argv);
}


/**
 * Set defaults, collect parameters, do sanity checking and call a function.
 *
 * \param f Function pointer or Tuple for class member functions.
 * \param argv Tuple containing arguments.
 * \param defs Parameter definitions.
 *
 * \return `true` on success, `false` otherwise.
 */
template <class F, class A, class D>
bool _parse(F f, A& argv, D& defs) {
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

/**
 * Parse user input and call a class member function.
 *
 * \ingroup eval
 *
 * \param m Tuple containing pointers to a class instance and a class member
 *   function.
 * \param defs Parameter definitions.
 *
 * \return `true` on success, `false` otherwise.
 */
template <TMEMB_T, class D>
bool parse(TMEMB& m, D& defs) {
  Tuple<FArgs...> argv;

  return _parse(m, argv, defs);
}

/**
 * Parse user input and call a function.
 *
 * \ingroup eval
 *
 * \param f Function pointer.
 * \param defs Parameter definitions.
 *
 * \return `true` on success, `false` otherwise.
 */
template <class R, class... FArgs, class D>
bool parse(R (*f)(FArgs...), D& defs) {
  Tuple<FArgs...> argv;

  return _parse(f, argv, defs);
}


/**
 * Select a function for parsing.
 *
 * \fn select(string, H, Args...)
 * \ingroup eval
 *
 * \param name Command name.
 * \param t Function definition under consideration.
 * \param args Remaining function definitions.
 *
 * \return `true` on success, `false` otherwise.
 */
inline bool select(string name) {
  IO.write("Unknown command: ", name, "\n");
  IO.flush();
  return false;
}

// Entry point.
template <class H, class... Args>
bool select(string name, H t, Args... args) {
  if (t.tail.head == name) {
    return parse(t.head, t.tail.tail.tail);
  }

  return select(name, args...);
}

#endif
