
#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>

void print_usage(char *prog_name) { printf("usage: %s file", prog_name); }

int main(int argc, char **argv) {
  if (argc != 2) {
    print_usage(argv[0]);
    exit(0);
  }

  return scan_file(argv[1]);
}