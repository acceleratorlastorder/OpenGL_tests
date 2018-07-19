/*
#define GL_FLOAT 0x1406
typedef float GLfloat;
*/
typedef struct VertexArray_t VertexArray_t;
typedef struct ArrayOfVertex_t ArrayOfVertex_t;
typedef struct Context_t Context_t, *ContextType;

/* Array of GLfloat since float is different depending the system it's better to
 use GLfloat to increase the portability of the program*/
struct VertexArray_t {
  int length;
  int sizeOfItems;
  float *array;
};


//Array of vertex Array
struct ArrayOfVertex_t {
  int length;
  int sizeOfItems;
  VertexArray_t *VertexArray_s;
};

//Creating a context to easily share necessary variable with any fucdtion function
struct Context_t {
  VertexArray_t VertexArray_s;
  ArrayOfVertex_t ArrayOfVertex_s;
};

/*  DATA TYPE management FUNCTIONS  */
void VertexArray_t_push(VertexArray_t *self, float el);
void VertexArray_t_initArray(VertexArray_t *self, int size);
void VertexArray_t_freeIt(VertexArray_t *self);
void ArrayOfVertex_t_push(ArrayOfVertex_t *self, VertexArray_t *verArr_s);
void ArrayOfVertex_t_initArray(ArrayOfVertex_t *self, int size);
