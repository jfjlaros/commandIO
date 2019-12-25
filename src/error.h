#ifndef USERIO_ERROR_H_
#define USERIO_ERROR_H_

#define SUCCESS 0
#define EEXCESSPARAM 1
#define EMISSINGVALUE 2
#define EPARAMTYPE 3
#define EUNKNOWNPARAM 4

const char* errorMessage[] = {
  "",
  "Excess parameter: ",
  "Missing value for parameter ",
  "Wrong type for parameter ",
  "Unknown parameter: "};

#endif
