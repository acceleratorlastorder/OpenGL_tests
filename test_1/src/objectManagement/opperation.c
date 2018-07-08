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

/*
//Array of vertex Array
struct ArrayOfVertex_t{
  int length;
  int sizeOfItems;
  void (*initArray)(ArrayOfVertex_t *, int size);
  void (*push)(ArrayOfVertex_t *, VertexArray_t arr);
  VertexArray_t **vertexArrays;
};*/

void ArrayOfVertex_t_push(ArrayOfVertex_t *self, VertexArray_t *verArr_s) {

  printf("wtf: %f\n", verArr_s -> array[2]);
  realloc(self->VertexArray_s, sizeof(self->VertexArray_s) + sizeof(VertexArray_t));
  self->VertexArray_s[self->length] = verArr_s;
  printf("wtf 222: %f\n", self->VertexArray_s[0] -> array[2]);
  self->length += 1;
  self->sizeOfItems = self->length * sizeof(VertexArray_t);
  return;
};

void ArrayOfVertex_t_initArray(ArrayOfVertex_t *self, int size) {
  self->VertexArray_s = malloc(size * sizeof(VertexArray_t));
  self->length = size;
  return;
};

void initArrayOfVertex_t(ArrayOfVertex_t *Array, int size) {
  Array->push = &ArrayOfVertex_t_push;
  Array->initArray = &ArrayOfVertex_t_initArray;
  Array->initArray(Array, size);
  return;
};
