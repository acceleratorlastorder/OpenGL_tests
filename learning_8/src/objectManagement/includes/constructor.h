#pragma once

#ifndef _constructor_h_
#define _constructor_h_

#include <cglm/call.h>
#include "../../../includes/glad/glad.h"


#include "./constructor_vertex.h"


typedef struct ScreenResolution_t ScreenResolution_t;
typedef struct CameraParamater_T CameraParamater_T;
typedef struct Context_t Context_t, *ContextType;

struct ScreenResolution_t {
  int width;
  int height;
  mat4 proj;
};

struct CameraParamater_T {
  vec3 eye;
  vec3 center;
  vec3 up;
  mat4 view;
};

//Creating a context to easily share necessary variable with any function
struct Context_t {
  GLuint vao;
  GLuint ebo;
  GLuint textureID;
  GLuint frameBuffer;
  GLuint shaderProgram;
  GLuint fragmentShader;
  GLuint vertexShader;
  GLint posAttrib;
  GLint colAttrib;
  GLint uniColor;
  GLint uniProj;
  GLint uniView;
  mat4 view;
  vec3 eye;
  mat4 position_model_mat;
  GLint uniModel;
  GLuint vbufferObj;
  GLuint vaoQuad;
  GLuint vboQuad;
  CameraParamater_T cameraParam;
  VertexBuferObjectArray_t VBO_ARRAY;
  GLuint VBO_FRAMEBUFFER;
  GLuint *vboArray;
  ScreenResolution_t monitorRes;
  VertexArray_t VertexArray_s;
  ArrayOfVertex_t ArrayOfVertex_s;
};


void init_mat4_with_GLM_MAT4_IDENTITY_INIT(mat4 matrice);

#endif /* _constructor_h_ */
