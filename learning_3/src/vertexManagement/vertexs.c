#ifdef debugBuild
#include <stdio.h>
#endif

#include "../../include/glad/glad.h"

#include <GLFW/glfw3.h>

#include "../../include/include.h"

#include "include/vertexs.h"

GLuint elements[] = {
    0, 1, 2,
    2, 3, 0
};

void uploadVertexOntoTheGPU(GLuint *vao, GLuint *vbufferObj, GLuint *ebo, Context_t *ctx) {

  glGenVertexArrays(1, vao);
  glBindVertexArray(*vao);

  glGenBuffers(1, vbufferObj);
#ifdef debugBuild
  printf("vbufferObj: %d\n", *vbufferObj);
#endif

glBindBuffer(GL_ARRAY_BUFFER, *vbufferObj);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,
    sizeof(elements), elements, GL_STATIC_DRAW);

#ifdef debugBuild
  printf("vbufferObj finished\n");
#endif
};

void getVertexs (Context_t *ctx){

};
