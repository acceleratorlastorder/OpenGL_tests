#include <stdio.h>
#include <time.h>
#include <windows.h>

#include <GLFW/glfw3.h>

#include "../../includes/include.h"
//#version 450 compatibility
double getMsBetweenFrame() { return (1 / framePerSec); }

// reset a string
void fillStringWithNull(char *stringToReset) {
  // printf("stringToReset as value AFTER: %s\n", stringToReset);
  memset(stringToReset, '\0', sizeof(*stringToReset));
  // printf("stringToReset as value BEFORE : %s\n", stringToReset);
}

// reset a string
void removeStringFromMemory(char *stringToReset) {
  // printf("stringToReset as value AFTER: %s\n", stringToReset);
  memset(&stringToReset, '\0', sizeof(*stringToReset));
  // printf("stringToReset as value BEFORE : %s\n", stringToReset);
}

void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}
