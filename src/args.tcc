#ifndef USERIO_ARGS_TCC_
#define USERIO_ARGS_TCC_

/// \defgroup args

#include "io.tcc"
#include "tuple.tcc"

extern RWIO IO;


/**
 * Count parameters.
 *
 * \fn countArgs(int&, int&, D&)
 * \ingroup args
 *
 * \param req Number of required parameters.
 * \param opt Number optional parameters.
 * \param defs Parameter definitions.
 */
inline void _countArgs(int& req, int& opt, Tuple<>&) {}

// Count required parameter.
template <PARG_T>
void _countArgs(int& req, int& opt, PARG& defs) {
  _countArgs(++req, opt, defs.tail);
}

// Count optional parameter.
template <class D>
void _countArgs(int& req, int& opt, D& defs) {
  _countArgs(req, ++opt, defs.tail);
}

// Entry point.
template <class D>
void countArgs(int& req, int& opt, D& defs) {
  _countArgs(req = 0, opt = 0, defs);
}


/**
 * Set default values.
 *
 * \fn setDefault(A&, D&)
 * \ingroup args
 *
 * \param argv Arguments.
 * \param defs Parameter definitions.
 */
inline void setDefault(Tuple<>&, Tuple<>&) {}

// Set required argument.
template <class A, PARG_T>
void setDefault(A& argv, PARG& defs) {
  convert(&argv.head, "0");
  setDefault(argv.tail, defs.tail);
}

// Set optional argument.
template <class A, class D>
void setDefault(A& argv, D& defs) {
  argv.head = defs.head.tail.head;
  setDefault(argv.tail, defs.tail);
}


/**
 * Update a required argument.
 *
 * \fn updateRequired(A&, D&, int, string&)
 * \ingroup args
 *
 * \param argv Arguments.
 * \param defs Parameter definitions.
 * \param num Argument number to update.
 * \param count Parameter number under consideration.
 * \param value Value.
 *
 * \return `true` on success, `false` otherwise.
 */
inline bool _updateRequired(Tuple<>&, Tuple<>&, int, int, string& value) {
  IO.err("Excess parameter: ", value, "\n");
  return false;
}

// Update a required argument.
template <class A, PARG_T>
bool _updateRequired(A& argv, PARG& defs, int num, int count, string& value) {
  if (num == count) {
    if (!convert(&argv.head, value)) {
      IO.write("Wrong type for parameter ", num + 1, "\n");
      return false;
    }
    return true;
  }

  return _updateRequired(argv.tail, defs.tail, num, count + 1, value);
}

// Skip optional parameters.
template <class A, class D>
bool _updateRequired(A& argv, D& defs, int num, int count, string& value) {
  return _updateRequired(argv.tail, defs.tail, num, count, value);
}

// Entry point.
template <class A, class D>
bool updateRequired(A& argv, D& defs, int num, string& value) {
  return _updateRequired(argv, defs, num, 0, value);
}


/**
 * Update an optional parameter value.
 *
 * \fn updateOptional(Tuple<H, Tail...>&, D&, string&)
 * \ingroup args
 *
 * \param argv Arguments.
 * \param defs Parameter definitions.
 * \param name Parameter name under consideration.
 *
 * \return `true` on success, `false` otherwise.
 */
inline bool updateOptional(Tuple<>&, Tuple<>&, string& name) {
  if (name != "-h" && name != "--help") {
    IO.err("Unknown parameter: ", name, "\n");
  }
  return false;
}

// Update flag parameter.
template <class... Tail, class D>
bool updateOptional(Tuple<bool, Tail...>& argv, D& defs, string& name) {
  if (defs.head.head == name) {
    argv.head = !argv.head;
    return true;
  }

  return updateOptional(argv.tail, defs.tail, name);
}

// Update optional parameter.
template <class H, class... Tail, class D>
bool updateOptional(Tuple<H, Tail...>& argv, D& defs, string& name) {
  if (defs.head.head == name) {
    if (!convert(&argv.head, IO.read())) {
      IO.err("Wrong type for parameter ", name, "\n");;
      return false;
    }
    return true;
  }

  return updateOptional(argv.tail, defs.tail, name);
}

#endif
