#ifndef _constructor_vertex_h_
#define _constructor_vertex_h_

#include "../../../includes/glad/glad.h"

typedef struct VertexAttribParameter_t VertexAttribParameter_t;
typedef struct ArrayOf_VertexAttribParameter_t ArrayOf_VertexAttribParameter_t;
typedef struct VertexBuferObjectArray_t VertexBuferObjectArray_t;
typedef struct VertexArray_t VertexArray_t;
typedef struct ArrayOfVertex_t ArrayOfVertex_t;
/*
*/
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

struct ArrayOf_VertexAttribParameter_t {
  size_t length;
  size_t sizeOfStructure;
  size_t sizeOfItems;
  size_t fullSizeOfArray;
  VertexAttribParameter_t *array;
};

struct VertexBuferObjectArray_t {
  size_t length;
  size_t usedSize;
  size_t sizeOfStructure;
  size_t sizeOfItems;
  GLuint *array;
};

/* Array of GLfloat since float is different depending the system it's better to
 use GLfloat to increase the portability of the program*/
struct VertexArray_t {
  size_t length;
  size_t usedSize;
  size_t sizeOfStructure;
  size_t sizeOfItems;
  GLfloat *array;
};

//Array of vertex Array
struct ArrayOfVertex_t {
  size_t length;
  size_t sizeOfStructure;
  size_t sizeOfItems;
  size_t fullSizeOfArray;
  VertexArray_t *VertexArray_s;
};


/*  DATA TYPE management FUNCTIONS  */
void VertexArray_t_allocate_effective_size(struct VertexArray_t *self);
void VertexArray_t_push(struct VertexArray_t *self, GLfloat el);
void VertexArray_t_initArray(struct VertexArray_t *self, size_t size);
void VertexArray_t_freeIt(struct VertexArray_t *self);
void ArrayOfVertex_t_push(struct ArrayOfVertex_t *self, struct VertexArray_t *verArr_s);
void ArrayOfVertex_t_freeIt(struct ArrayOfVertex_t *self);
void ArrayOfVertex_t_initArray(struct ArrayOfVertex_t *self, size_t size);
void VertexBuferObjectArray_t_push(struct VertexBuferObjectArray_t *self, GLuint el);
void ArrayOf_VertexAttribParameter_t_initArray(struct ArrayOf_VertexAttribParameter_t *self, size_t size);
void ArrayOf_VertexAttribParameter_t_push(struct ArrayOf_VertexAttribParameter_t *self, struct VertexAttribParameter_t *verAttrib_s);


#endif /* _constructor_vertex_h_  */
