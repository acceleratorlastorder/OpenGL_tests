#define GL_FLOAT 0x1406
typedef float GLfloat;

typedef struct VertexArray_t VertexArray_t;
typedef struct ArrayOfVertex_t ArrayOfVertex_t;

struct VertexArray_t {
  size_t length;
  size_t usedSize;
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

void VertexArray_t_push(struct VertexArray_t *self, GLfloat el);
void VertexArray_t_initArray(struct VertexArray_t *self, size_t size);
void VertexArray_t_freeIt(struct VertexArray_t *self);
void ArrayOfVertex_t_push(struct ArrayOfVertex_t *self,
                          struct VertexArray_t *verArr_s);
void ArrayOfVertex_t_initArray(struct ArrayOfVertex_t *self, size_t size);
void VertexArray_t_allocate_effective_size(struct VertexArray_t *self);
