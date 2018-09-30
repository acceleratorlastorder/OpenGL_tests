#include <stdio.h>
#include <time.h>
#include <windows.h>

#include <GLFW/glfw3.h>
#include <cglm/call.h>

#include "../../includes/include.h"
#include "./includes/opperation.h"
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

void print_mat4(mat4 mat){
  printf("mat4 {\n");
  for (size_t i = 0; i < 4; i++) {
    if (i == 3) {
      printf("  [%f], [%f], [%f], [%f]\n", mat[i][0], mat[i][1], mat[i][2], mat[i][3]);
    }else{
      printf("  [%f], [%f], [%f], [%f],\n", mat[i][0], mat[i][1], mat[i][2], mat[i][3]);
    }
  }
  printf("}\n");
}

void print_mat3(mat3 mat){
  printf("mat3 {\n");
  for (size_t i = 0; i < 3; i++) {
    if (i == 2) {
      printf("  [%f], [%f], [%f]\n", mat[i][0], mat[i][1], mat[i][2]);
    }else{
      printf("  [%f], [%f], [%f],\n", mat[i][0], mat[i][1], mat[i][2]);
    }
  }
  printf("}\n");
}
