#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

// exit program with error message
void FAIL(const char *label);

// for classes that should not be copied
struct nocopy {
  nocopy() = default;
  nocopy(const nocopy &) = delete;
  nocopy &operator=(const nocopy &) = delete;
};

#endif
