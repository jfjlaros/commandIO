#pragma once

#include "error.h"
#include "types.tcc"

/// \defgroup args


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
template <class... Args>
void _countArgs(
    int& req, int& opt,
    Tuple<Tuple<const char*, const char*>, Args...>& defs) {
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
template <class A, class... Args>
void setDefault(
    A& argv, Tuple<Tuple<const char*, const char*>, Args...>& defs) {
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
 * \return success on success, an error code otherwise.
 */
inline int _updateRequired(Tuple<>&, Tuple<>&, int, int, string&) {
  return eExcessParam;
}

// Update a required argument.
template <class A, class... Args>
int _updateRequired(
    A& argv, Tuple<Tuple<const char*, const char*>, Args...>& defs,
    int num, int count, string& value) {
  if (num == count) {
    if (!convert(&argv.head, value)) {
      return eParamType;
    }
    return success;
  }

  return _updateRequired(argv.tail, defs.tail, num, count + 1, value);
}

template <class T, class... Args>
int _updateRequired(
    Tuple<vector<T>>& argv, Tuple<Tuple<const char*, const char*>, Args...>&,
    int, int, string& value) {
  if (!convert(&argv.head, value)) {
    return eParamType;
  }
  return success;
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
 * \return success on success, an error code otherwise.
 */
template <class I>
int updateOptional(I&, Tuple<>&, Tuple<>&, string&) {
  return eUnknownParam;
}

// Update flag parameter.
template <class I, class... Tail, class D>
int updateOptional(I& io, Tuple<bool, Tail...>& argv, D& defs, string& name) {
  if (defs.head.head == name) {
    argv.head = !argv.head;
    return success;
  }

  return updateOptional(io, argv.tail, defs.tail, name);
}

// Update optional parameter.
template <class I, class H, class... Tail, class D>
int updateOptional(I& io, Tuple<H, Tail...>& argv, D& defs, string& name) {
  if (defs.head.head == name) {
    if (io.eol()) {
      return eMissingValue;
    }
    if (!convert(&argv.head, io.read())) {
      return eParamType;
    }
    return success;
  }

  return updateOptional(io, argv.tail, defs.tail, name);
}
