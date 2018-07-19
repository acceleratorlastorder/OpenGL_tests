#ifdef debugBuild
#include <stdio.h>
#endif

#include "../../includes/glad/glad.h"

#include <GLFW/glfw3.h>

#include "../../includes/include.h"

#include "../objectManagement/includes/constructor.h"

#include "includes/vertexs.h"


GLfloat triangle[] = {
    0.0f,  0.5f,  // Vertex 1 (X, Y)
    0.5f,  -0.5f, // Vertex 2 (X, Y)
    -0.5f, -0.5f  // Vertex 3 (X, Y)
};

GLfloat triangleColored[] = {
    0.0f,  0.5f,  1.0f, 0.0f, 0.0f, // Vertex 1 (X, Y, Red, Green, Blue): Red
    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 1 (X, Y, Red, Green, Blue): Green
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 1 (X, Y, Red, Green, Blue): Blue
};


GLfloat cube[] = {
  1.000000f, -1.000000f, -1.000000f,
  1.000000f, -1.000000f, 1.000000f,
  -1.000000f, -1.000000f, 1.000000f,
  -1.000000f, -1.000000f, -1.000000f,
  1.000000f, 1.000000f, -1.000000f,
  1.000000f, 1.000000f, 1.000001f,
  -1.000000f, 1.000000f, 1.000000f,
  -1.000000f, 1.000000f, -1.000000f
};


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
