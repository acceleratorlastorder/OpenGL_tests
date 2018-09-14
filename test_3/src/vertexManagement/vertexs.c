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

size_t triangleColoredSize = 15;

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
float vertices[] = {
    -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
    -0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
};

GLuint elements[] = {
    0, 1, 2,
    2, 3, 0
};

void uploadVertexOntoTheGPU(Context_t *ctx) {

  glGenVertexArrays(1, &ctx -> vao);
  glBindVertexArray(ctx -> vao);

  glGenBuffers(1, &ctx -> vbufferObj);
#ifdef debugBuild
  printf("vbufferObj: %d\n", ctx -> vbufferObj);
#endif

glBindBuffer(GL_ARRAY_BUFFER, ctx -> vbufferObj);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ctx -> ebo);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

#ifdef debugBuild
  printf("vbufferObj finished\n");
#endif
};

void getVertexs (Context_t *ctx){
  //TODO: future evol get this from a .obj file or more to construct the vertexs
  for (size_t i = 0; i < triangleColoredSize; i++) {
    VertexArray_t_push(&ctx -> VertexArray_s, triangleColored[i]);
  }
  return;
};
