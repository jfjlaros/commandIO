#ifndef USERIO_ARGS_TCC_
#define USERIO_ARGS_TCC_

/// \defgroup args

#include "error.h"
#include "types.tcc"


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
inline void _countArgs(int&, int&, Tuple<>&) {}

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
 * \return SUCCESS on success, an error code otherwise.
 */
inline int _updateRequired(Tuple<>&, Tuple<>&, int, int, string&) {
  return EEXCESSPARAM;
}

// Update a required argument.
template <class A, PARG_T>
int _updateRequired(A& argv, PARG& defs, int num, int count, string& value) {
  if (num == count) {
    if (!convert(&argv.head, value)) {
      return EPARAMTYPE;
    }
    return SUCCESS;
  }

  return _updateRequired(argv.tail, defs.tail, num, count + 1, value);
}

template <class T, PARG_T>
int _updateRequired(
    Tuple<vector<T>>& argv, PARG&, int, int, string& value) {
  if (!convert(&argv.head, value)) {
    return EPARAMTYPE;
  }
  return SUCCESS;
}

// Skip optional parameters.
template <class A, class D>
int _updateRequired(A& argv, D& defs, int num, int count, string& value) {
  return _updateRequired(argv.tail, defs.tail, num, count, value);
}

// Entry point.
template <class A, class D>
int updateRequired(A& argv, D& defs, int num, string& value) {
  return _updateRequired(argv, defs, num, 0, value);
}


/**
 * Update an optional parameter value.
 *
 * \fn updateOptional(Tuple<H, Tail...>&, D&, string&)
 * \ingroup args
 *
 * \param io Input / output object.
 * \param argv Arguments.
 * \param defs Parameter definitions.
 * \param name Parameter name under consideration.
 *
 * \return SUCCESS on success, an error code otherwise.
 */
template <class I>
int updateOptional(I&, Tuple<>&, Tuple<>&, string&) {
  return EUNKNOWNPARAM;
}

// Update flag parameter.
template <class I, class... Tail, class D>
int updateOptional(I& io, Tuple<bool, Tail...>& argv, D& defs, string& name) {
  if (defs.head.head == name) {
    argv.head = !argv.head;
    return SUCCESS;
  }

  return updateOptional(io, argv.tail, defs.tail, name);
}

// Update optional parameter.
template <class I, class H, class... Tail, class D>
int updateOptional(I& io, Tuple<H, Tail...>& argv, D& defs, string& name) {
  if (defs.head.head == name) {
    if (io.eol()) {
      return EMISSINGVALUE;
    }
    if (!convert(&argv.head, io.read())) {
      return EPARAMTYPE;
    }
    return SUCCESS;
  }

  return updateOptional(io, argv.tail, defs.tail, name);
}

#endif
