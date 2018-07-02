#define isFullscreen 0
#define framePerSec 60


double getMsBetweenFrame();
void getFile(char *charArray, char *filePath);
void fillStringWithNull(char *stringToReset);
void removeStringFromMemory(char *stringToReset);
void error_callback(int error, const char *description);
void setBootstrapConfig(void);

void compileVertexShader(char *vertexShaderSource, GLuint *shaderProgram, GLuint *vertexShader);
void compileFragmentShader(char *fragmentShaderSource, GLuint *shaderProgram, GLuint *fragmentShader);
void loadShaders(GLuint *shaderProgram, GLuint *fragmentShader, GLuint *vertexShader);
void uploadVertexOntoTheGPU();
void setShadersAttributes(GLuint *shaderProgram, GLint *posAttrib, GLint *colAttrib);
