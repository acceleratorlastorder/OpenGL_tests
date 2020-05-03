#include <cglm/call.h>
typedef int GLint;
typedef unsigned int GLuint;
typedef float GLfloat;


typedef struct Coodinate_2D Coodinate_2D;
typedef struct Coodinate_3D Coodinate_3D;

typedef struct VertexArray_t VertexArray_t;
typedef struct ArrayOfVertex_t ArrayOfVertex_t;
typedef struct Context_t Context_t, *ContextType;

struct Coodinate_2D {
 GLfloat X;
 GLfloat Y;
};

struct Coodinate_3D {
  GLfloat X;
  GLfloat Y;
  GLfloat Z;
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

//Creating a context to easily share necessary variable with any function
struct Context_t {
  GLuint vao;
  GLuint ebo;
  GLuint textureID;
  GLuint vbufferObj;
  GLuint shaderProgram;
  GLuint fragmentShader;
  GLuint vertexShader;
  GLint posAttrib;
  GLint colAttrib;
  GLint uniColor;
  GLint uniProj;
  GLint uniView;
  mat4 view;
  vec3 eye;
  mat4 position_model_mat;
  GLint uniModel;
  vec3 center;
  vec3 up;
  VertexArray_t VertexArray_s;
  ArrayOfVertex_t ArrayOfVertex_s;
};

/*  DATA TYPE management FUNCTIONS  */
void VertexArray_t_allocate_effective_size(struct VertexArray_t *self);
void VertexArray_t_push(struct VertexArray_t *self, GLfloat el);
void VertexArray_t_initArray(struct VertexArray_t *self, size_t size);
void VertexArray_t_freeIt(struct VertexArray_t *self);
void ArrayOfVertex_t_push(struct ArrayOfVertex_t *self, struct VertexArray_t *verArr_s);
void ArrayOfVertex_t_freeIt(struct ArrayOfVertex_t *self);
void ArrayOfVertex_t_initArray(struct ArrayOfVertex_t *self, size_t size);
void init_mat4_with_GLM_MAT4_IDENTITY_INIT(mat4 matrice);
