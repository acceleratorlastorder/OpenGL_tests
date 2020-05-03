#include <stdio.h>
#include <time.h>
#include <windows.h>

#include <GLFW/glfw3.h>
#include <cglm/call.h>

#include "../../includes/include.h"
#include "./includes/opperation.h"
//#version 450 compatibility
double getMsBetweenFrame() { return (1 / framePerSec); }

/**
 * [fillStringWithNull Fills the whole string with the NULL char "/0" so it's still in the memory but filled with null]
 * @param stringToReset [description]
 */
void fillStringWithNull(char *stringToReset) {
  /* printf("stringToReset as value AFTER: %s\n", stringToReset); */
  memset(stringToReset, '\0', sizeof(*stringToReset));
  /* printf("stringToReset as value BEFORE : %s\n", stringToReset); */
}

/**
 * [removeStringFromMemory Remove the string from the memory]
 * @param stringToReset [The name is explicit enough... i hope ? :) ]
 */
void removeStringFromMemory(char *stringToReset) {
  // printf("stringToReset as value AFTER: %s\n", stringToReset);
  memset(&stringToReset, '\0', sizeof(*stringToReset));
  // printf("stringToReset as value BEFORE : %s\n", stringToReset);
}

void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

/**
 * [print_mat4 description]
 * @param mat       [description]
 * @param printMode [description]
 */
void print_mat4(mat4 mat, signed short printMode){
  printf("mat4 {\n");
  for (size_t i = 0; i < 4; i++) {
    if (i == 3) {
      if (printMode == 0) {
        printf("  [%f], [%f], [%f], [%f]\n", mat[i][0], mat[i][1], mat[i][2], mat[i][3]);
      }else{
        printf("  [%p], [%p], [%p], [%p]\n", &mat[i][0], &mat[i][1], &mat[i][2], &mat[i][3]);
      }
    }else{
      if (printMode == 0) {
        printf("  [%f], [%f], [%f], [%f],\n", mat[i][0], mat[i][1], mat[i][2], mat[i][3]);
      }else{
        printf("  [%p], [%p], [%p], [%p],\n", &mat[i][0], &mat[i][1], &mat[i][2], &mat[i][3]);
      }
    }
  }
  printf("}\n");
};

/**
 * [print_mat3 description]
 * @param mat [description]
 */
void print_mat3(mat3 mat, signed short printMode){
  printf("mat3 {\n");
  for (size_t i = 0; i < 3; i++) {
    if (i == 2) {
      printf("  [%f], [%f], [%f]\n", mat[i][0], mat[i][1], mat[i][2]);
      if (printMode == 0) {
        printf("  [%f], [%f], [%f]\n", mat[i][0], mat[i][1], mat[i][2]);
      }else{
        printf("  [%p], [%p], [%p]\n", &mat[i][0], &mat[i][1], &mat[i][2]);
      }
    }else{
      if (printMode == 0) {
        printf("  [%f], [%f], [%f],\n", mat[i][0], mat[i][1], mat[i][2]);
      }else{
        printf("  [%p], [%p], [%p],\n", &mat[i][0], &mat[i][1], &mat[i][2]);
      }
    }
  }
  printf("}\n");
}
