#ifdef debugBuild
#include <stdio.h>
#endif

#include "../../includes/glad/glad.h"

#include <GLFW/glfw3.h>
#include <cglm/call.h>

#include "../../includes/include.h"

#include "../objectManagement/includes/constructor.h"


/**
* [Compiling the given shader onto the GPU]
*/
void compileVertexShader(char *vertexShaderSource, GLuint *shaderProgram,
                         GLuint *vertexShader) {
  glShaderSource(*vertexShader, 1, (const GLchar **)(&vertexShaderSource),
                 NULL);
  glCompileShader(*vertexShader);

#ifdef debugBuild
  GLint status;
  glGetShaderiv(*vertexShader, GL_COMPILE_STATUS, &status);

  if (status == GL_TRUE) {
    printf("vertex shader is corectly loaded\n");

  } else {
    printf("vertex shader got problem\n");
  }

  char buffer[512];
  glGetShaderInfoLog(*vertexShader, 512, NULL, buffer);
  printf("log for the vertex shader: %s\n", buffer);
#endif
  // glAttachShader(*shaderProgram, *vertexShader);
}

/**
* [Compiling the given fragment shader onto the GPU]
*/
void compileFragmentShader(char *fragmentShaderSource, GLuint *shaderProgram,
                           GLuint *fragmentShader) {

  glShaderSource(*fragmentShader, 1, (const GLchar **)(&fragmentShaderSource),
                 NULL);
  glCompileShader(*fragmentShader);

  GLint status;
  glGetShaderiv(*fragmentShader, GL_COMPILE_STATUS, &status);

#ifdef debugBuild
  if (status == GL_TRUE) {
    printf("fragment shader is corectly loaded\n");
  } else {
    printf("fragment shader got problem\n");
  }
  char buffer[512];
  glGetShaderInfoLog(*fragmentShader, 512, NULL, buffer);
  printf("log for fragment the shader: %s\n", buffer);
#endif
  // glAttachShader(*shaderProgram, *fragmentShader);
}

void loadShaders(GLuint *shaderProgram, GLuint *fragmentShader,
                 GLuint *vertexShader) {
  char fileContent[666];
  char *filePath = "includes/shaders/vertexShader.glsl";

  // get shader
  // printf("filePath: %s\n", filePath);
  readFile(fileContent, filePath);
  *shaderProgram = glCreateProgram();
  *vertexShader = glCreateShader(GL_VERTEX_SHADER);
  compileVertexShader(fileContent, shaderProgram, vertexShader);

  // reset string
  fillStringWithNull(fileContent);

  // get fragment shader
  filePath = "includes/shaders/fragmentShader.frag";
  // printf("fileContent: %s\n", filePath);
  readFile(fileContent, filePath);

  *fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  compileFragmentShader(fileContent, shaderProgram, fragmentShader);

  //   attach vertex shader
  glAttachShader(*shaderProgram, *vertexShader);
  //   attach fragment shader
  glAttachShader(*shaderProgram, *fragmentShader);
  glBindFragDataLocation(*shaderProgram, 0, "outColor");

  // remove string
  removeStringFromMemory(fileContent);

  glLinkProgram(*shaderProgram);
  glUseProgram(*shaderProgram);

  return;
}

void setShadersAttributes(Context_t *ctx) {

  ctx -> posAttrib = glGetAttribLocation(ctx -> shaderProgram, "position");
  glEnableVertexAttribArray(ctx -> posAttrib);
  glVertexAttribPointer(ctx -> posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);

  ctx -> colAttrib = glGetAttribLocation(ctx -> shaderProgram, "color");
  glEnableVertexAttribArray(ctx -> colAttrib);
  glVertexAttribPointer(ctx -> colAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
  /*
  ctx -> textureID = glGetAttribLocation(ctx -> shaderProgram, "texcoord");
  glEnableVertexAttribArray(ctx -> textureID);
  glVertexAttribPointer(ctx -> textureID, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(6 * sizeof(GLfloat)));
  */
  // SET THE MATRIX POINTER
  ctx -> uniModel = glGetUniformLocation(ctx -> shaderProgram, "model");

  return;
}

void reloadShaders(Context_t *ctx){
  glDeleteProgram(ctx -> shaderProgram);
  glDeleteShader(ctx -> fragmentShader);
  glDeleteShader(ctx -> vertexShader);
  loadShaders(&ctx -> shaderProgram, &ctx -> fragmentShader, &ctx -> vertexShader);
  setShadersAttributes(ctx);
}
