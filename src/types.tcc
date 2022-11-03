#pragma once

#include <sstream>
#include <string>
#include <vector>

#include "tuple.tcc"

using std::string;
using std::istringstream;
using std::vector;


/*
 * Type naming functions.
 */

inline string typeOf(bool) {
  return "bool";
}

inline string typeOf(char) {
  return "char";
}

inline string typeOf(signed char) {
  return "signed char";
}

inline string typeOf(unsigned char) {
  return "unsigned char";
}

inline string typeOf(short int) {
  return "short int";
}

inline string typeOf(unsigned short int) {
  return "unsigned short int";
}

inline string typeOf(int) {
  return "int";
}

inline string typeOf(unsigned int) {
  return "unsigned int";
}

inline string typeOf(long int) {
  return "long int";
}

inline string typeOf(unsigned long int) {
  return "unsigned long int";
}

inline string typeOf(long long int) {
  return "long long int";
}

inline string typeOf(unsigned long long int) {
  return "unsigned long long int";
}

inline string typeOf(float) {
  return "float";
}

inline string typeOf(double) {
  return "double";
}

inline string typeOf(long double) {
  return "long double";
}

inline string typeOf(string&) {
  return "string";
}

template <class T>
string typeOf(vector<T>&) {
  T data {};
  return "vector<" + typeOf(data) + ">";
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

template <class T>
bool convert(vector<T>* data, string s) {
  T value;
  bool status = convert(&value, s);
  data->push_back(value);

  return status;
}
