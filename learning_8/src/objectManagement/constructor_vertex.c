#include "stdio.h"
#include "stdlib.h"

#include "includes/constructor_vertex.h"


struct VertexAttribParameter_t {
  /*index*/
  GLint attributeLocation;
  /**/
  GLint size;
  /*type of the values to read*/
  GLenum type;
  /**/
  GLboolean normalized;
  /*gap between the next value in the array (yeah i can't really explain, a picture show it better)*/
  GLsizei stride;
  /**/
  GLvoid *pointer;
  /*name to use for those value, will be used then in shaders*/
  char *name;
};

void ArrayOf_VertexAttribParameter_t_push(struct ArrayOf_VertexAttribParameter_t *self,
                          struct VertexAttribParameter_t *verArr_s) {

  self->sizeOfItems += sizeof(*verArr_s);

  // Create temp value to keep the original array safe and avoid memory leak
  VertexArray_t *tempArray = realloc(self->VertexArray_s, self->sizeOfItems);
  // Check if everything happend normally
  if (tempArray == 0) {
    puts("couldn't re-allocate the memory to push in the function "
         "ArrayOf_VertexAttribParameter_t_push()!!");
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
  }

  // As we just added an element we increment it by one
  self->length += 1;

  /************************************************************************************
   * Here we simply keep track of the size in byte of the "self" structure,           *
   *    as we simply push a new structure into the array of structure,                *
   *    we simply add on top of previously given byte size "verArr_s -> sizeOfItems", *                                                *
   *    since the last level array structure follow the same logic and                *
   *    keep track of it's size                                                       *
   ************************************************************************************/
  self->sizeOfItems += verArr_s->sizeOfStructure;
  return;
};


void VertexBuferObjectArray_t_push(struct VertexBuferObjectArray_t *self, GLuint el) {
  if (self->array == NULL && self->length != 0) {
    puts("the pointer \"self->array\" is null in the function "
         "VertexArray_t_push() !! Can't push anything there");
    //VertexArray_t_freeIt(self);
    return;
  } else {
    // Create temp value to keep the original array safe and avoid memory leak
    GLuint *tempArray =
        realloc(self->array, (self->length * sizeof(GLuint)) + sizeof(el));
    // check if everything happend normally
    if (tempArray == 0) {
      puts("couldn't re-allocate the memory to push in the function "
           "VertexArray_t_push()!!");
      //VertexArray_t_freeIt(self);
      return;
    }
    self->array = tempArray;
    self->array[self->usedSize] = el;
    self->length += 1;
    self->usedSize += 1;
    self->sizeOfItems += sizeof(GLuint);
    self->sizeOfStructure += sizeof(GLuint);
    return;
  }
};

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
  // First of all i free all memory block each array pointer possess
  for (size_t i = self->length; i-- > 0;) {
    VertexArray_t_freeIt(&self->VertexArray_s[i]);
  }

  // Then i simply free the vertexArray_s, as i freed all array inside i just
  // have to free the container array
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
