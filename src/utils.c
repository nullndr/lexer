#include "utils.h"

char *
allocate_chars(const char *__src, unsigned int __n) {
  char *__dest = malloc(sizeof(char) * __n + 1);
  memcpy(__dest, __src, __n);
  __dest[__n] = '\0';
  return __dest;
}