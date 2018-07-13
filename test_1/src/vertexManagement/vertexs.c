#ifdef debugBuild
#include <stdio.h>
#endif

#include "../../include/glad/glad.h"

#include <GLFW/glfw3.h>

#include "../../include/include.h"

#include "include/vertexs.h"


void uploadVertexOntoTheGPU(GLuint *vbufferObj, Context_t *ctx) {

  glGenBuffers(1, vbufferObj);
#ifdef debugBuild
  printf("vbufferObj: %d\n", *vbufferObj);
#endif
  glBindBuffer(GL_ARRAY_BUFFER, *vbufferObj); // BIND current vbo as array
                                              // buffer and make it current
                                              // active arrayBuff

  glBufferData(GL_ARRAY_BUFFER, ctx->VertexArray_s.sizeOfItems,
               ctx->VertexArray_s.array, GL_STATIC_DRAW);

#ifdef debugBuild
  printf("vbufferObj finished\n");
#endif
};

void getVertexs (Context_t *ctx){

};
