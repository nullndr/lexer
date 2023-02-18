
#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FILE_DOES_NOT_EXISTS                                                   \
  "\x1b[1m\x1b[31merror\x1b[0m: the file \x1b[1m'%s'\x1b[0m does not exists"

#define FILE_CANT_BE_READ                                                      \
  "\x1b[1m\x1b[31merror\x1b[0m: the file \x1b[1m'%s'\x1b[0m can't be read"

char *allocate_chars(const char *__src, unsigned __n);

#endif