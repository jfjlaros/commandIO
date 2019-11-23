#ifndef USERIO_TYPES_TCC_
#define USERIO_TYPES_TCC_

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


/*
 * Conversion functions.
 */

void _convert(bool* data, string s) {
  *data = (bool)stoi(s);
}

void _convert(char* data, string s) {
  *data = (char)stoi(s);
}

void _convert(signed char* data, string s) {
  *data = (signed char)stoi(s);
}

void _convert(unsigned char* data, string s) {
  *data = (unsigned char)stoi(s);
}

void _convert(short int* data, string s) {
  *data = (short int)stoi(s);
}

void _convert(unsigned short int* data, string s) {
  *data = (unsigned short int)stoi(s);
}

void _convert(int* data, string s) {
  *data = stoi(s);
}

void _convert(unsigned int* data, string s) {
  *data = (unsigned int)stoi(s);
}

void _convert(long int* data, string s) {
  *data = stol(s);
}

void _convert(unsigned long int* data, string s) {
  *data = stoul(s);
}

void _convert(long long int* data, string s) {
  *data = stoll(s);
}

void _convert(unsigned long long int* data, string s) {
  *data = stoull(s);
}

void _convert(float* data, string s) {
  *data = stof(s);
}

void _convert(double* data, string s) {
  *data = stod(s);
}

void _convert(long double* data, string s) {
  *data = stold(s);
}

void _convert(string* data, string s) {
  *data = s;
}

/**
 * Convert a string to any type.
 *
 * \param data Result of the conversion.
 * \param s Input of the conversion.
 *
 * \return `true` if the conversion was successful, `false` otherwise.
 */
template <class T>
bool convert(T* data, string s) {
  try {
    _convert(data, s);
  }
  catch (std::invalid_argument) {
    return false;
  }
  return true;
}

#endif
