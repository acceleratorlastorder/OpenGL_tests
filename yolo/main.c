#include "stdio.h"
#include "stdlib.h"
#include <time.h>


#define GL_FLOAT 0x1406
typedef float GLfloat;

typedef struct VertexArray_t VertexArray_t;
typedef struct ArrayOfVertex_t ArrayOfVertex_t;

struct VertexArray_t {
  size_t length;
  size_t sizeOfStructure;
  size_t sizeOfItems;
  GLfloat *array;
};

struct ArrayOfVertex_t {
  size_t length;
  size_t sizeOfStructure;
  size_t sizeOfItems;
  VertexArray_t *VertexArray_s;
};

void VertexArray_t_push(struct VertexArray_t *self, GLfloat el) {
  //printf("bef realloc self->array %d\n", self->array);
  realloc(self->array, sizeof(self->array) + sizeof(el));
  //printf("after realloc self->array %d\n", self->array);
  self->array[self->length] = el;
  self->length += 1;
  self->sizeOfItems += sizeof(el);
  self->sizeOfStructure = sizeof(el);
  return;
}
void VertexArray_t_initArray(struct VertexArray_t *self, size_t size) {
  self->length = size;
  self->array = malloc(size * sizeof(GLfloat));
  self->sizeOfItems = sizeof(self->array);
  self->sizeOfStructure = sizeof(*self);
  return;
}

void VertexArray_t_freeIt(struct VertexArray_t *self) {
  free(self->array);
  self->length = 0;
  self->sizeOfItems = sizeof(self->length) + sizeof(self->sizeOfItems);
  return;
}

void ArrayOfVertex_t_push(struct ArrayOfVertex_t *self, struct VertexArray_t *verArr_s) {

  realloc(self->VertexArray_s, sizeof(self->VertexArray_s) + sizeof(*verArr_s));


  // I give all property of the given structure into the new one
  self->VertexArray_s[self->length] = *verArr_s;


  // Allocation of memory and also removing the reference to the previous pointer,
  //      which will be usefull if the structure is freed we can keep this array
  self->VertexArray_s[self->length].array = malloc(*verArr_s->array);

  // Assign freshly allocated array with value from the old array
  for (size_t i = verArr_s->length; i-- > 0;) {
    self->VertexArray_s[self->length].array[i] = verArr_s->array[i];
  }

  // As we just added an element we increment it by one
  self->length += 1;

  // Here we simply keep track of the size in byte of the "self" structure,
  //    as we simply push a new structure into the array of structure,
  //        we simply add on top of previously given byte size "verArr_s -> sizeOfItems",
  //          since the last level array structure follow the same logic and keep track of it's size
  self->sizeOfItems += verArr_s->sizeOfStructure;
  return;
}

void ArrayOfVertex_t_initArray(struct ArrayOfVertex_t *self, size_t size) {
  self->VertexArray_s = malloc(size * sizeof(VertexArray_t));
  self->length = size;
  self->sizeOfItems = sizeof(*self);
  return;
}

int main() {
  printf("INIT !\n");
  VertexArray_t testGLfloatArrStruct;
  VertexArray_t_initArray(&testGLfloatArrStruct, 0);

  ArrayOfVertex_t testArrayOfGLfloatArrStruct;
  ArrayOfVertex_t_initArray(&testArrayOfGLfloatArrStruct, 0);

  clock_t start_t, end_t, total_t;

  start_t = clock();
  printf("Starting of the program, start_t = %ld\n", start_t);

  for (size_t i = 0; i < 7000; i++) {
    VertexArray_t_push(&testGLfloatArrStruct, 654646.56f);
  }
  end_t = clock();
  printf("End of the big loop, end_t = %ld\n", end_t);

  total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
  printf("Total time taken by CPU: %ld\n", total_t);

  /*testGLfloatArrStruct.array[0] = 666.66f;
  testGLfloatArrStruct.array[1] = 666.66f;
  testGLfloatArrStruct.array[2] = 666.66f;
  testGLfloatArrStruct.array[3] = 666.66f;
  testGLfloatArrStruct.array[4] = 666.66f;

  testGLfloatArrStruct.array[5] = 666.66f;
  testGLfloatArrStruct.array[6] = 666.66f;
  testGLfloatArrStruct.array[7] = 666.66f;
  testGLfloatArrStruct.array[8] = 666.66f;
  testGLfloatArrStruct.array[9] = 666.66f;*/

  printf("yolo !\n");
  ArrayOfVertex_t_push(&testArrayOfGLfloatArrStruct, &testGLfloatArrStruct);
  printf("yolo !\n");
  VertexArray_t_freeIt(&testGLfloatArrStruct);

  printf("testArrayOfGLfloatArrStruct.VertexArray_s[0].array[0] %f\n", testArrayOfGLfloatArrStruct.VertexArray_s[0].array[0]);
  printf("testArrayOfGLfloatArrStruct.VertexArray_s[0].array[1] %f\n", testArrayOfGLfloatArrStruct.VertexArray_s[0].array[1]);
  printf("testArrayOfGLfloatArrStruct.VertexArray_s[0].array[2] %f\n", testArrayOfGLfloatArrStruct.VertexArray_s[0].array[2]);

  printf("yolo !\n");
  scanf("yolo \n");
  return 0;
}

/*
gcc main.c -g -Wall -Wextra -ansi -pedantic -std=c11 -O3 -g
*/
