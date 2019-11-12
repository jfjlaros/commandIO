#ifndef SIMPLE_REPL_ARGS_TCC_
#define SIMPLE_REPL_ARGS_TCC_

#include "io.tcc"
#include "tuple.tcc"

extern RWIO IO;


/**
 * Count parameters.
 *
 * @param req Number of required parameters.
 * @param opt Number optional parameters.
 * @param defs Parameter definitions.
 */
inline void _countArgs(int& req, int& opt, Tuple<>&) {}

/// @private Required parameter.
template <PARG_T>
void _countArgs(int& req, int& opt, PARG& defs) {
  _countArgs(++req, opt, defs.tail);
}

/// @private Optional parameter.
template <class D>
void _countArgs(int& req, int& opt, D& defs) {
  _countArgs(req, ++opt, defs.tail);
}

/// Count parameters.
template <class D>
void countArgs(int& req, int& opt, D& defs) {
  _countArgs(req = 0, opt = 0, defs);
}


/*
 * Set default values.
 *
 * @param argv Actual parameters.
 * @param defs Parameter definitions.
 */
inline void setDefault(Tuple<>&, Tuple<>&) {}

/// @private Required parameter.
template <class A, PARG_T>
void setDefault(A& argv, PARG& defs) {
  convert(&argv.head, "0");
  setDefault(argv.tail, defs.tail);
}

/// @private Optional parameter.
template <class A, class D>
void setDefault(A& argv, D& defs) {
  argv.head = defs.head.tail.head;
  setDefault(argv.tail, defs.tail);
}


/*
 * Update a required parameter value.
 *
 * @param argv Actual parameters.
 * @param defs Parameter definitions.
 * @param num Parameter number to update.
 * @param count Parameter number under consideration.
 * @param value Value.
 *
 * @return @a true on success, @a false otherwise.
 */
inline bool _updateRequired(Tuple<>&, Tuple<>&, int, int, string& value) {
  IO.err("Excess parameter: ", value, "\n");
  return false;
}

/// @private Required parameter.
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

/// @private Optional parameter.
template <class A, class D>
bool _updateRequired(A& argv, D& defs, int num, int count, string& value) {
  return _updateRequired(argv.tail, defs.tail, num, count, value);
}

/// Update a required parameter value.
template <class A, class D>
bool updateRequired(A& argv, D& defs, int num, string& value) {
  return _updateRequired(argv, defs, num, 0, value);
}


/*
 * Update an optional parameter value.
 *
 * @param argv Actual parameters.
 * @param defs Parameter definitions.
 * @param name Parameter name under consideration.
 *
 * @return @a true on success, @a false otherwise.
 */
inline bool updateOptional(Tuple<>&, Tuple<>&, string name) {
  if (name != "-h" && name != "--help") {
    IO.err("Unknown parameter: ", name, "\n");
  }
  return false;
}

/// @private Flag parameter.
template <class... Tail, class D>
bool updateOptional(Tuple<bool, Tail...>& argv, D& defs, string name) {
  if (defs.head.head == name) {
    argv.head = !argv.head;
    return true;
  }

  return updateOptional(argv.tail, defs.tail, name);
}

/// @private Optional parameter.
template <class H, class... Tail, class D>
bool updateOptional(Tuple<H, Tail...>& argv, D& defs, string name) {
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
