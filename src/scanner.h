
#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"

typedef struct scanner_t {
  char *start;
  char *current;
  char *current_line;
  location loc;
} scanner_t;

typedef enum { SCANNER_OK, SCANNER_FILE_ERROR } scanner_result;

scanner_result scan_file(const char *const file_path);

#endif