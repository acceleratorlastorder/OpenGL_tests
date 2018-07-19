#include "stdio.h"
#include "stdlib.h"

#include "includes/constructor.h"

void VertexArray_t_push(VertexArray_t *self, float el) {
  realloc(self->array, self->sizeOfItems + sizeof(el));
  self->array[self->length] = el;
  self->length += 1;
  self->sizeOfItems += sizeof(el);
  return;
};

void VertexArray_t_initArray(VertexArray_t *self, int size) {
  self->array = malloc(size * sizeof(float));
  self->length = size;
  self->sizeOfItems = size * sizeof(float);
  return;
};

void VertexArray_t_freeIt(VertexArray_t *self) {
  printf("free it !\n");
  free(self->array);
  self->length = 0;
  self->sizeOfItems = 0;
  printf("freed !\n");
  return;
};

void ArrayOfVertex_t_push(ArrayOfVertex_t *self, VertexArray_t *verArr_s) {
  realloc(self->VertexArray_s, self->sizeOfItems + verArr_s->sizeOfItems);

  // I give all property of the given structure into the new one
  self->VertexArray_s[self->length] = *verArr_s;

  // Allocation of memory and also removing the reference to the previous pointer,
  //      which will be usefull if the structure is freed we can keep this array
  self->VertexArray_s[self->length].array = malloc(verArr_s->sizeOfItems);

  // assign freshly allocated array with value from the old array
  for (size_t i = verArr_s->length; i-- > 0;) {
    self->VertexArray_s[self->length].array[i] = verArr_s->array[i];
  }

  // As we just added an element we increment it by one
  self->length += 1;

  // Here we simply keep track of the size in byte of the "self" structure,
  //    as we simply push a new structure into the array of structure,
  //        we simply add on top of previously given byte size "verArr_s -> sizeOfItems",
  //          since the last level array structure follow the same logic and keep track of it's size
  self->sizeOfItems += (verArr_s->sizeOfItems + sizeof(verArr_s->length) + sizeof(verArr_s->sizeOfItems));
  return;
};

void ArrayOfVertex_t_initArray(ArrayOfVertex_t *self, int size) {
  self->VertexArray_s = malloc(size * sizeof(VertexArray_t));
  self->length = size;
  self->sizeOfItems = sizeof(size) + sizeof(self->sizeOfItems);
  return;
};
