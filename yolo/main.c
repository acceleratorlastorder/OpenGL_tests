// There you'll only find some workaround/improvement for the functions i used
// in my learning and test session,
//
// first improvement : fix of the reference bug since i was giving a pointer once i
//        free the original i lost it on the array of structure as i use pointer and i freed it
//
// second improvement better tracking of the items byte size

#include "stdio.h"
#include "stdlib.h"

typedef struct FloatArray_t FloatArray_t, *ArrayType;
typedef struct ArrayOfFloatArray_t ArrayOfFloatArray_t, *ArrayOfVertexType;

struct FloatArray_t {
  int length;
  int sizeOfItems;
  void (*initArray)(FloatArray_t *, int size);
  void (*push)(FloatArray_t *, float el);
  void (*freeIt)(FloatArray_t *);
  float *array;
};

struct ArrayOfFloatArray_t {
  int length;
  int sizeOfItems;
  void (*initArray)(ArrayOfFloatArray_t *, int size);
  void (*push)(ArrayOfFloatArray_t *, FloatArray_t *verArr);
  FloatArray_t *FloatArray_s;
};

void FloatArray_t_push(FloatArray_t *self, float el) {
  realloc(self->array, sizeof(self->array) + sizeof(float));
  self->array[self->length] = el;
  self->length += 1;
  self->sizeOfItems += sizeof(el);
  return;
};
void FloatArray_t_initArray(FloatArray_t *self, int size) {
  self->array = malloc(size * sizeof(float));
  self->length = size;
  self->sizeOfItems = sizeof(size) + sizeof(self->sizeOfItems);
  return;
};

void FloatArray_t_freeIt(FloatArray_t *self) {
  free(self->array);
  self->length = 0;
  return;
};

void initFloatArray_t(FloatArray_t *Array, int size) {
  Array->push = &FloatArray_t_push;
  Array->initArray = &FloatArray_t_initArray;
  Array->freeIt = &FloatArray_t_freeIt;
  Array->initArray(Array, size);
  return;
};

void ArrayOfFloatArray_t_push(ArrayOfFloatArray_t *self,
                              FloatArray_t *verArr_s) {

  realloc(self->FloatArray_s, sizeof(self->FloatArray_s) + verArr_s->sizeOfItems);


  // i give all property of the given structure into the new one
  self->FloatArray_s[self->length] = *verArr_s;
  // alocation of memory and also removing the reference to the previous pointer,
  //      which will be usefull if the structure is freed we can keep this array
  self->FloatArray_s[self->length].array = malloc(verArr_s->length * sizeof(float));

  // assign freshly allocated array with value from the old array
  for (size_t i = verArr_s->length; i-- > 0;) {
    self->FloatArray_s[self->length].array[i] = verArr_s->array[i];
  }

  // As we just added an element we increment it by one
  self->length += 1;

  // here we simply keep track of the size in byte of the "self" structure,
  //    as we simply push a new structure into the array of structure,
  //        we simply add on top of previously given byte size "verArr_s -> sizeOfItems",
  //          since the last level array structure follow the same logic and keep track of it's size
  self->sizeOfItems += verArr_s->sizeOfItems;
  return;
};

void ArrayOfFloatArray_t_initArray(ArrayOfFloatArray_t *self, int size) {
  self->FloatArray_s = malloc(size * sizeof(FloatArray_t));
  self->length = size;
  self->sizeOfItems = sizeof(size) + sizeof(self->sizeOfItems);
  return;
};

void initArrayOfFloatArray_t(ArrayOfFloatArray_t *Array, int size) {
  Array->push = &ArrayOfFloatArray_t_push;
  Array->initArray = &ArrayOfFloatArray_t_initArray;
  Array->initArray(Array, size);
  return;
};

int main(int argc, char const *argv[]) {
  printf("INIT !\n");
  FloatArray_t testFloatArrStruct;
  initFloatArray_t(&testFloatArrStruct, 0);

  ArrayOfFloatArray_t testArrayOfFloatArrStruct;
  initArrayOfFloatArray_t(&testArrayOfFloatArrStruct, 0);

  testFloatArrStruct.push(&testFloatArrStruct, 666.0f);
  testFloatArrStruct.push(&testFloatArrStruct, 6646545646.0f);
  testFloatArrStruct.push(&testFloatArrStruct, 6545646.0f);

  testArrayOfFloatArrStruct.push(&testArrayOfFloatArrStruct,
                                 &testFloatArrStruct);

  testFloatArrStruct.freeIt(&testFloatArrStruct);

  printf("testArrayOfFloatArrStruct.FloatArray_s[0].array[0] %f \n", testArrayOfFloatArrStruct.FloatArray_s[0].array[0]);
  printf("testArrayOfFloatArrStruct.FloatArray_s[0].array[1] %f \n", testArrayOfFloatArrStruct.FloatArray_s[0].array[1]);

  scanf("yolo \n");
  return 0;
}
