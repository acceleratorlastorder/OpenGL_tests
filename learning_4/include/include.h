#define isFullscreen 0
#define framePerSec 60
#define usedVertex 1

// Window dimensions
typedef struct {
  int width;
  int height;
} screenRes;

//Yeah i'm trying to OO C XD
typedef struct VertexArray_t VertexArray_t, *ArrayType;
typedef struct ArrayOfVertex_t ArrayOfVertex_t, *ArrayOfVertexType;
typedef struct Context_t Context_t, *ContextType;

/* Array of GLfloat since float is different depending the system it's better to
 use GLfloat to increase the portability of the program*/
struct VertexArray_t {
  int length;
  int sizeOfItems;
  void (*initArray)(VertexArray_t *, int size);
  void (*push)(VertexArray_t *, GLfloat el);
  GLfloat *array;
};

//Array of vertex Array
struct ArrayOfVertex_t{
  int length;
  int sizeOfItems;
  void (*initArray)(ArrayOfVertex_t *, int size);
  void (*push)(ArrayOfVertex_t *, VertexArray_t *verArr);
  VertexArray_t **VertexArray_s;
};

//Creating a context to easily share necessary variable with any function
struct Context_t {
  GLuint vao;
  GLuint ebo;
  GLuint vbufferObj;
  GLuint shaderProgram;
  GLuint fragmentShader;
  GLuint vertexShader;
  GLint posAttrib;
  GLint colAttrib;
  VertexArray_t VertexArray_s;
  ArrayOfVertex_t ArrayOfVertex_s;
};

char usableVertex[3][50];
/*  DATA TYPE management FUNCTIONS  */
void VertexArray_t_push(VertexArray_t *self, GLfloat el);
void VertexArray_t_initArray(VertexArray_t *self, int size);
void initVertexArray_t(VertexArray_t *Array, int size);

void ArrayOfVertex_t_push(ArrayOfVertex_t *self, VertexArray_t *verArr);
void ArrayOfVertex_t_initArray(ArrayOfVertex_t *self, int size);
void initArrayOfVertex_t(ArrayOfVertex_t *Array, int size);


void getVertexs (Context_t *ctx);
void uploadVertexOntoTheGPU(Context_t *ctx);


double getMsBetweenFrame();
void readFile(char *charArray, char *filePath);
void fillStringWithNull(char *stringToReset);
void removeStringFromMemory(char *stringToReset);
void error_callback(int error, const char *description);
void setBootstrapConfig(void);

/* SHADERS MANAGEMENT */
void compileVertexShader(char *vertexShaderSource, GLuint *shaderProgram, GLuint *vertexShader);
void compileFragmentShader(char *fragmentShaderSource, GLuint *shaderProgram, GLuint *fragmentShader);
void loadShaders(GLuint *shaderProgram, GLuint *fragmentShader, GLuint *vertexShader);
void setShadersAttributes(GLuint *shaderProgram, GLint *posAttrib, GLint *colAttrib);
