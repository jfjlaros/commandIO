#pragma once

#include <string>

#include "error.h"
#include "tuple.tcc"

/// \defgroup eval

using std::string;


/*
 * Recursion terminators.
 *
 * All parameters have been collected. All values are now present in the `args`
 * parameter pack.
 */

// Void class member function.
template <class I, class C, class P, class... FArgs, class... Args>
void _call(
    I&, Tuple<C*, void (P::*)(FArgs...)>& m, Tuple<>&, Args&... args) {
  (*m.head.*m.tail.head)(args...);
}

// Void function.
template <class I, class... FArgs, class... Args>
void _call(I&, void (*f)(FArgs...), Tuple<>&, Args&... args) {
  f(args...);
}

// Class member function that returns a value.
template <class I, class C, class R, class P, class... FArgs, class... Args>
void _call(
    I& io, Tuple<C*, R (P::*)(FArgs...)>& m, Tuple<>&, Args&... args) {
  print(io, (*m.head.*m.tail.head)(args...), "\n");
}

// Function that returns a value.
template <class I, class F, class... Args>
void _call(I& io, F f, Tuple<>&, Args&... args) {
  print(io, f(args...), "\n");
}


/*
 * Parameter collection.
 *
 * The first member of the tuple `argv` is added to the parameter pack `args`.
 */
template <class I, class F, class A, class... Args>
void _call(I& io, F f, A& argv, Args&... args) {
  _call(io, f, argv.tail, args..., argv.head);
}


/**
 * Call a class member function.
 *
 * \ingroup eval
 *
 * \param io Input / output object.
 * \param m Tuple containing pointers to a class instance and a class member
 *   function.
 * \param argv Tuple containing arguments.
 */
template <class I, class C, class R, class P, class... FArgs, class A>
void call(I& io, Tuple<C*, R (P::*)(FArgs...)>& m, A& argv) {
  _call(io, m, argv);
}

/**
 * Call a function.
 *
 * \ingroup eval
 *
 * \param io Input / output object.
 * \param f Function pointer.
 * \param argv Tuple containing arguments.
 */
template <class I, class F, class A>
void call(I& io, F f, A& argv) {
  _call(io, f, argv);
}


/**
 * Set defaults, collect parameters, do sanity checking and call a function.
 *
 * \param io Input / output object.
 * \param f Function pointer or Tuple for class member functions.
 * \param argv Tuple containing arguments.
 * \param defs Parameter definitions.
 *
 * \return `true` on success, `false` otherwise.
 */
template <class I, class F, class A, class D>
bool _parse(I& io, F f, A& argv, D& defs) {
  string token = "";
  int errorCode,
      opt,
      req,
      number = 0;

  setDefault(argv, defs);

  while (!io.eol()) {
    token = io.read();

    if (token[0] == '-') {
      if (token == "-h" || token == "--help") {
        return false;
      }

      errorCode = updateOptional(io, argv, defs, token);

      switch (errorCode) {
        case success:
          continue;
        case eUnknownParam:
          break;
        default:
          print(io, errorMessage[errorCode], token, "\n");
          return false;
      }
    }

    errorCode = updateRequired(argv, defs, number, token);

    switch (errorCode) {
      case success:
        number++;
        continue;
      default:
        print(io, errorMessage[errorCode], number + 1, "\n");
        return false;
    }
  }

  countArgs(req, opt, defs);

  if (number < req) {
    print(io, "Required parameter missing.\n");
    return false;
  }

  call(io, f, argv);

  return true;
}

/**
 * Parse user input and call a class member function.
 *
 * \ingroup eval
 *
 * \param io Input / output object.
 * \param m Tuple containing pointers to a class instance and a class member
 *   function.
 * \param defs Parameter definitions.
 *
 * \return `true` on success, `false` otherwise.
 */
template <class I, class C, class R, class P, class... FArgs, class D>
bool parse(I& io, Tuple<C*, R (P::*)(FArgs...)>& m, D& defs) {
  Tuple<FArgs...> argv;

  return _parse(io, m, argv, defs);
}

/**
 * Parse user input and call a function.
 *
 * \ingroup eval
 *
 * \param io Input / output object.
 * \param f Function pointer.
 * \param defs Parameter definitions.
 *
 * \return `true` on success, `false` otherwise.
 */
template <class I, class R, class... FArgs, class D>
bool parse(I& io, R (*f)(FArgs...), D& defs) {
  Tuple<FArgs...> argv;

  return _parse(io, f, argv, defs);
}


/**
 * Select a function for parsing.
 *
 * \fn select(string, H, Args...)
 * \ingroup eval
 *
 * \param io Input / output object.
 * \param name Command name.
 * \param t Function definition under consideration.
 * \param args Remaining function definitions.
 *
 * \return `true` on success, `false` otherwise.
 */
template <class I>
bool select(I& io, string name) {
  print(io, "Unknown command: ", name, "\n");
  io.flush();
  return false;
}

// Entry point.
template <class I, class H, class... Args>
bool select(I& io, string name, H t, Args... args) {
  if (t.tail.head == name) {
    return parse(io, t.head, t.tail.tail.tail);
  }

  return select(io, name, args...);
}
