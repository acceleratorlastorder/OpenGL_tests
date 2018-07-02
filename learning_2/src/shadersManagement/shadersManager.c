#ifdef debugBuild
#include <stdio.h>
#endif

#include "../../include/glad/glad.h"

#include <GLFW/glfw3.h>

#include "../../include/include.h"

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

  if (status == GL_TRUE) {
#ifdef debugBuild
    printf("fragment shader is corectly loaded\n");
#endif
  } else {
#ifdef debugBuild
    printf("fragment shader got problem\n");
#endif
  }
#ifdef debugBuild
  char buffer[512];
  glGetShaderInfoLog(*fragmentShader, 512, NULL, buffer);
  printf("log for fragment the shader: %s\n", buffer);
#endif
  // glAttachShader(*shaderProgram, *fragmentShader);
}

void loadShaders(GLuint *shaderProgram, GLuint *fragmentShader,
                 GLuint *vertexShader) {
  char fileContent[666];
  char *filePath = "include/shaders/vertexShader.glsl";

  // get shader
  // printf("filePath: %s\n", filePath);
  getFile(fileContent, filePath);
  *shaderProgram = glCreateProgram();
  *vertexShader = glCreateShader(GL_VERTEX_SHADER);
  compileVertexShader(fileContent, shaderProgram, vertexShader);

  // reset string
  fillStringWithNull(fileContent);

  // get fragment shader
  filePath = "include/shaders/fragmentShader.frag";
  // printf("fileContent: %s\n", filePath);
  getFile(fileContent, filePath);

  *fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  compileFragmentShader(fileContent, shaderProgram, fragmentShader);

  glAttachShader(*shaderProgram, *vertexShader);
  glAttachShader(*shaderProgram, *fragmentShader);
  glBindFragDataLocation(*shaderProgram, 0, "outColor");

  // remove string
  removeStringFromMemory(fileContent);

  glLinkProgram(*shaderProgram);
  glUseProgram(*shaderProgram);

  return;
}

void setShadersAttributes(GLuint *shaderProgram, GLint *posAttrib, GLint *colAttrib) {

  *posAttrib = glGetAttribLocation(*shaderProgram, "position");
  glEnableVertexAttribArray(*posAttrib);
  glVertexAttribPointer(*posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                        0);

  *colAttrib = glGetAttribLocation(*shaderProgram, "color");
  glEnableVertexAttribArray(*colAttrib);
  glVertexAttribPointer(*colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                        (void *)(2 * sizeof(GLfloat)));

  return;
}
