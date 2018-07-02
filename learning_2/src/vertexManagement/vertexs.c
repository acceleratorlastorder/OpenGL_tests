#ifdef debugBuild
#include <stdio.h>
#endif

#include "../../include/glad/glad.h"

#include <GLFW/glfw3.h>

#include "../../include/include.h"

#include "include/vertexs.h"

void uploadVertexOntoTheGPU(GLuint *vbufferObj) {

  glGenBuffers(1, vbufferObj);
#ifdef debugBuild
  printf("vbufferObj: %d\n", *vbufferObj);
#endif
  glBindBuffer(GL_ARRAY_BUFFER, *vbufferObj); // BIND current vbo as array buffer and make it current active arrayBuff
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticesColored), verticesColored, GL_STATIC_DRAW);
#ifdef debugBuild
  printf("vbufferObj finished\n");
#endif
}
