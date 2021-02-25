#include "print.h"

#include <stdio.h>

void PrintError(char* message) {
  fprintf(stderr, "\033[0;31mError:\033[0m %s\n", message);
}

void PrintWarning(char* message) {
  printf("\033[0;33mWarning:\033[0m %s\n", message);
}