#ifndef USERIO_TYPES_TCC_
#define USERIO_TYPES_TCC_

#include <sstream>
#include <string>

#include "tuple.tcc"

using std::string;
using std::istringstream;

#define PARG_T class... Args
#define PARG Tuple<Tuple<const char*, const char*>, Args...>


/*
 * Type naming functions.
 */

inline string typeof(bool) {
  return "bool";
}

inline string typeof(char) {
  return "char";
}

inline string typeof(signed char) {
  return "signed char";
}

inline string typeof(unsigned char) {
  return "unsigned char";
}

inline string typeof(short int) {
  return "short int";
}

inline string typeof(unsigned short int) {
  return "unsigned short int";
}

inline string typeof(int) {
  return "int";
}

inline string typeof(unsigned int) {
  return "unsigned int";
}

inline string typeof(long int) {
  return "long int";
}

inline string typeof(unsigned long int) {
  return "unsigned long int";
}

inline string typeof(long long int) {
  return "long long int";
}

inline string typeof(unsigned long long int) {
  return "unsigned long long int";
}

inline string typeof(float) {
  return "float";
}

inline string typeof(double) {
  return "double";
}

inline string typeof(long double) {
  return "long double";
}

inline string typeof(string&) {
  return "string";
}


/**
 * Convert a string to any type.
 *
 * \param data Result of the conversion.
 * \param s Input of the conversion.
 *
 * \return `true` if the conversion was successful, `false` otherwise.
 */
inline bool convert(string* data, string s) {
  *data = s;

  return true;
}

template <class T>
bool convert(T* data, string s) {
  istringstream iss(s);

  iss >> *data;

  return !iss.fail();
}

#endif
