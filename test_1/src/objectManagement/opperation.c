#include <stdio.h>
#include <time.h>
#include <windows.h>

#include <GLFW/glfw3.h>

#include "../../include/include.h"
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

void VertexArray_t_push(VertexArray_t *self, GLfloat el) {
  realloc(self->array, sizeof(self->array) + sizeof(GLfloat));
  self->array[self->length] = el;
  self->length += 1;
  self->sizeOfItems = self->length * sizeof(GLfloat);
  return;
};

void VertexArray_t_initArray(VertexArray_t *self, int size) {
  self->array = malloc(size * sizeof(GLfloat));
  self->length = size;
  return;
};

void initVertexArray_t(VertexArray_t *Array, int size) {
  Array->push = &VertexArray_t_push;
  Array->initArray = &VertexArray_t_initArray;
  Array->initArray(Array, size);
  return;
};
