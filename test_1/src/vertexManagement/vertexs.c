#ifdef debugBuild
#include <stdio.h>
#endif

#include "../../include/glad/glad.h"

#include <GLFW/glfw3.h>

#include "../../include/include.h"

#include "include/vertexs.h"


void uploadVertexOntoTheGPU(GLuint *vbufferObj, Context_t *ctx) {

  /*
  printf("triangle length: %d\n", sizeof(triangle));
  printf("triangleColored length: %d\n", sizeof(triangleColored));
  printf("cube length: %d\n", sizeof(cube));
  printf("verticesArray length: %d\n", (sizeof(verticesArray)/sizeof(float)));
  int i = (sizeof(verticesArray[0])/sizeof(float));
  printf("i length: %d\n", i);
  for (; i-- > 0;) {
    printf("verticesArray %d: %f\n",i, verticesArray[0][i]);
  }

  */

  float *arr = malloc(10 * sizeof(float));
  arr[0] = 112345.0f;
  arr[1] = 560.0f;
  arr[2] = 7.0f;
  arr[3] = 6.0f;

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
