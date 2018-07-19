typedef struct VertexArray_t VertexArray_t;
typedef struct ArrayOfVertex_t ArrayOfVertex_t;

struct VertexArray_t {
  int length;
  int sizeOfItems;
  GLfloat *array;
};

struct ArrayOfVertex_t {
  int length;
  int sizeOfItems;
  VertexArray_t *VertexArray_s;
};
void VertexArray_t_push(VertexArray_t *self, GLfloat el);
void VertexArray_t_initArray(VertexArray_t *self, int size);
void ArrayOfVertex_t_push(ArrayOfVertex_t *self, VertexArray_t *verArr_s);
void ArrayOfVertex_t_initArray(ArrayOfVertex_t *self, int size);
