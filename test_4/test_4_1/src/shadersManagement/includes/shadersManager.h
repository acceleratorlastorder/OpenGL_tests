void compileVertexShader(char *vertexShaderSource, GLuint *shaderProgram, GLuint *vertexShader);
void compileFragmentShader(char *fragmentShaderSource, GLuint *shaderProgram, GLuint *fragmentShader);
void loadShaders(GLuint *shaderProgram, GLuint *fragmentShader, GLuint *vertexShader);
void setShadersAttributes(Context_t *ctx);
void reloadShaders(Context_t *ctx);
