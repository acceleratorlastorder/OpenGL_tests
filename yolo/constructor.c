/********************************************************
 *  gcc constructor.c -g -Wall -Wextra -std=c11 -O3 -g  *
 ********************************************************/

#include "stdio.h"
#include "stdlib.h"
#include <time.h>

#include "constructor.h"

void VertexArray_t_allocate_effective_size(struct VertexArray_t *self) {
  if (self->array == NULL && self->length != 0) {
    puts(
        "the pointer \"self->array\" is null in the function "
        "VertexArray_t_allocate_effective_size() !! Can't push anything there");
    VertexArray_t_freeIt(self);
    return;
  } else {
    // Create temp value to keep the original array safe and avoid memory leak
    GLfloat *tempArray = realloc(self->array, self->usedSize * sizeof(GLfloat));
    // check if everything happend normally
    if (tempArray == 0) {
      puts("couldn't re-allocate the memory to push in the function "
           "VertexArray_t_allocate_effective_size()!!");
      VertexArray_t_freeIt(self);
      return;
    }
    self->array = tempArray;
    self->sizeOfItems = self->usedSize * sizeof(GLfloat);
    self->sizeOfStructure = sizeof(*self) + self->sizeOfItems;
    self->length = self->usedSize;
    return;
  }
}

void VertexArray_t_push(struct VertexArray_t *self, GLfloat el) {
  if (self->array == NULL && self->length != 0) {
    puts("the pointer \"self->array\" is null in the function "
         "VertexArray_t_push() !! Can't push anything there");
    VertexArray_t_freeIt(self);
    return;
  } else {
    // Create temp value to keep the original array safe and avoid memory leak
    GLfloat *tempArray =
        realloc(self->array, (self->length * sizeof(GLfloat)) + sizeof(el));
    // check if everything happend normally
    if (tempArray == 0) {
      puts("couldn't re-allocate the memory to push in the function "
           "VertexArray_t_push()!!");
      VertexArray_t_freeIt(self);
      return;
    }
    self->array = tempArray;
    self->array[self->usedSize] = el;
    self->length += 1;
    self->usedSize += 1;
    self->sizeOfItems += sizeof(GLfloat);
    self->sizeOfStructure += sizeof(GLfloat);
    return;
  }
}

void VertexArray_t_push_with_margin(struct VertexArray_t *self, GLfloat el) {
  if (self->array == NULL && self->length != 0) {
    puts("the pointer \"self->array\" is null in the function "
         "VertexArray_t_push() !! Can't push anything there");
    VertexArray_t_freeIt(self);
    return;
  } else {
    if (self->usedSize == self->length) {
      if (self->length == 0) {
        self->sizeOfItems = sizeof(GLfloat);
        self->length = 1;
        self->sizeOfStructure += sizeof(GLfloat);
      } else {
        // Define the margin length
        self->sizeOfItems = self->length * sizeof(GLfloat) * 2;
        self->sizeOfStructure += (self->length * sizeof(GLfloat) * 2) -
                                 (self->length * sizeof(GLfloat));
        self->length *= 2;
      }
      // Create temp value to keep the original array safe and avoid memory leak
      GLfloat *tempArray = realloc(self->array, self->sizeOfItems);
      // Check if everything happend normally
      if (tempArray == 0) {
        puts("couldn't re-allocate the memory to push in the function "
             "VertexArray_t_push_with_margin()!!");
        VertexArray_t_freeIt(self);
        return;
      }
      // Assign the original array the temp array value after check
      self->array = tempArray;
    }

    self->array[self->usedSize] = el;
    self->usedSize += 1;
    return;
  }
}

void VertexArray_t_initArray(struct VertexArray_t *self, size_t size) {
  self->sizeOfItems = size * sizeof(GLfloat);
  self->array = malloc(self->sizeOfItems);
  if (self->array == NULL) {
    puts("memory allocation failed at VertexArray_t_initArray()");
    self->sizeOfItems = 0;
    return;
  }
  self->length = size;
  self->usedSize = 0;
  self->sizeOfStructure = sizeof(*self) + self->sizeOfItems;

  return;
}

void VertexArray_t_freeIt(struct VertexArray_t *self) {
  free(self->array);
  self->length = 0;
  self->sizeOfItems = 0;
  self->sizeOfStructure = sizeof(*self);

  return;
}

void ArrayOfVertex_t_push(struct ArrayOfVertex_t *self,
                          struct VertexArray_t *verArr_s) {

  printf("sizeof(verArr_s) %I64d\n", sizeof(*verArr_s));

  printf("sizeof(verArr_s) %I64d\n", sizeof(verArr_s->array));

  printf("sizeof(verArr_s) %I64d\n",
         (verArr_s->length * sizeof(verArr_s->array[0])));

  self->sizeOfItems += sizeof(*verArr_s);

  // Create temp value to keep the original array safe and avoid memory leak
  VertexArray_t *tempArray = realloc(self->VertexArray_s, self->sizeOfItems);
  // Check if everything happend normally
  if (tempArray == 0) {
    puts("couldn't re-allocate the memory to push in the function "
         "VertexArray_t_push_with_margin()!!");
    ArrayOfVertex_t_freeIt(self);
    return;
  }
  // Assign the original array the temp array value after check
  self->VertexArray_s = tempArray;

  // I give all property of the given structure into the new one
  self->VertexArray_s[self->length] = *verArr_s;

  // Allocation of memory and also removing the reference to the previous
  // pointer,
  //      which will be usefull if the structure is freed we can keep this array
  self->VertexArray_s[self->length].array =
      malloc((verArr_s->length * sizeof(verArr_s->array[0])));
  // Assign freshly allocated array with value from the old array
  for (size_t i = verArr_s->length; i-- > 0;) {
    self->VertexArray_s[self->length].array[i] = verArr_s->array[i];
    printf("self->VertexArray_s[%I64d].array[%I64d] %f\n", self->length, i, self->VertexArray_s[self->length].array[i]);
  }

  // As we just added an element we increment it by one
  self->length += 1;

  // Here we simply keep track of the size in byte of the "self" structure,
  //    as we simply push a new structure into the array of structure,
  //        we simply add on top of previously given byte size "verArr_s ->
  //        sizeOfItems",
  //          since the last level array structure follow the same logic and
  //          keep track of it's size
  self->sizeOfItems += verArr_s->sizeOfStructure;
  return;
}

void ArrayOfVertex_t_freeIt(struct ArrayOfVertex_t *self) {
  for (size_t i = self->length; i-- > 0;) {
    VertexArray_t_freeIt(&self->VertexArray_s[i]);
  }

  free(self->VertexArray_s);
  self->length = 0;
  self->sizeOfItems = 0;
  self->sizeOfStructure = sizeof(*self);

  return;
}

void ArrayOfVertex_t_initArray(struct ArrayOfVertex_t *self, size_t size) {
  self->sizeOfItems = size * sizeof(VertexArray_t);
  self->VertexArray_s = malloc(self->sizeOfItems);
  if (self->VertexArray_s == NULL) {
    puts("memory allocation failed at ArrayOfVertex_t_initArray()");
    self->sizeOfItems = 0;
    return;
  }
  self->length = size;
  self->sizeOfStructure = sizeof(*self) + self->sizeOfItems;
  return;
}

int main() {
  printf("INIT !\n");

  VertexArray_t testGLfloatArrStruct;
  VertexArray_t_initArray(&testGLfloatArrStruct, 0);

  ArrayOfVertex_t testArrayOfGLfloatArrStruct;
  ArrayOfVertex_t_initArray(&testArrayOfGLfloatArrStruct, 0);

  clock_t start_t, end_t;
  double total_t;
  start_t = clock();
  printf("Starting of the program, start_t = %ld\n", start_t);
  for (size_t j = 0; j < 5; j++) {
    for (size_t i = 0; i < 5; i++) {
      // VertexArray_t_push(&testGLfloatArrStruct, 654646.56f);
      // arrayTestStruct_t_push(&testArr, i + 666.56f);
      VertexArray_t_push_with_margin(&testGLfloatArrStruct, i + 666.56f);
      // printf("testArr-> array[%d]%f\n", i, testArr.array[i]);
    }
    printf("yolo !\n");
    printf("size of length: %I64d\n", testGLfloatArrStruct.length);
    printf("size of structure: %I64d\n", testGLfloatArrStruct.sizeOfStructure);
    printf("size of items: %I64d\n", testGLfloatArrStruct.sizeOfItems);
    printf("testGLfloatArrStruct.array[%I64d] %f\n",
           (testGLfloatArrStruct.usedSize - 1),
           testGLfloatArrStruct.array[(testGLfloatArrStruct.usedSize - 1)]);
    VertexArray_t_allocate_effective_size(&testGLfloatArrStruct);
    printf("after effective size testGLfloatArrStruct.array[%I64d] %f\n",
           (testGLfloatArrStruct.usedSize - 1),
           testGLfloatArrStruct.array[testGLfloatArrStruct.usedSize - 1]);
    printf("size of structure after effective size: %I64d\n",
           testGLfloatArrStruct.sizeOfStructure);
    printf("size of items after effective size: %I64d\n",
           testGLfloatArrStruct.sizeOfItems);
    ArrayOfVertex_t_push(&testArrayOfGLfloatArrStruct, &testGLfloatArrStruct);
    printf("free !\n");
    VertexArray_t_freeIt(&testGLfloatArrStruct);
    printf("size of structure after free: %I64d\n",
           testGLfloatArrStruct.sizeOfStructure);
    printf("size of items after free: %I64d\n",
           testGLfloatArrStruct.sizeOfItems);
    printf("Re-init !\n");
    VertexArray_t_initArray(&testGLfloatArrStruct, 0);
    printf("Re-inited !\n");
    printf("YES !\n");
  }
  end_t = clock();
  printf("End of the big loop, end_t = %ld\n", end_t);

  printf("total time as ms = %ld\n", (end_t - start_t));

  total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
  printf("Total time taken by CPU: %lf\n", total_t);

  printf("yolo !\n");
  //  ArrayOfVertex_t_push(&testArrayOfGLfloatArrStruct, &testGLfloatArrStruct);
  printf("yolo !\n");
  //  VertexArray_t_freeIt(&testGLfloatArrStruct);

  printf("testGLfloatArrStruct.array[0] %f\n", testGLfloatArrStruct.array[0]);
  printf("testGLfloatArrStruct.array[1] %f\n", testGLfloatArrStruct.array[1]);
  printf("testGLfloatArrStruct.array[2] %f\n", testGLfloatArrStruct.array[2]);

  printf("testArrayOfGLfloatArrStruct.VertexArray_s[0].array[0] %f\n",
         testArrayOfGLfloatArrStruct.VertexArray_s[0].array[0]);
  printf("testArrayOfGLfloatArrStruct.VertexArray_s[0].array[1] %f\n",
         testArrayOfGLfloatArrStruct.VertexArray_s[0].array[1]);
  printf("testArrayOfGLfloatArrStruct.VertexArray_s[0].array[2] %f\n",
         testArrayOfGLfloatArrStruct.VertexArray_s[0].array[2]);

  printf("ENNNND !\n");
  scanf("yolo \n");
  return 0;
}
