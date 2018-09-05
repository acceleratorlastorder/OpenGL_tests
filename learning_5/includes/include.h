#define isFullscreen 0
#define framePerSec 60
#define usedVertex 1


// Window dimensions
typedef struct {
  int width;
  int height;
} screenRes;

char usableVertex[3][50];


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
void setShadersAttributes(GLuint *shaderProgram, GLint *posAttrib, GLint *colAttrib, GLuint *tex);
