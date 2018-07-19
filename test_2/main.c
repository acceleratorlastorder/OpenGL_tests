#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "includes/glad/glad.h"

#include <GLFW/glfw3.h>

#include "includes/include.h"

#include "src/objectManagement/includes/constructor.h"
#include "src/vertexManagement/includes/vertexs.h"

screenRes monitorRes = {.width = 800, .height = 600};


void setBootstrapConfig(void) {
  glfwSetErrorCallback(error_callback);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  return;
};

void loadObject(GLuint *vao, GLuint *vbufferObj, GLuint *shaderProgram,
                GLuint *fragmentShader, GLuint *vertexShader, GLint *posAttrib,
                GLint *colAttrib, Context_t *openGL_program_ctx) {
  glGenVertexArrays(1, vao);
  glBindVertexArray(*vao);

  uploadVertexOntoTheGPU(vbufferObj, openGL_program_ctx);
  loadShaders(shaderProgram, fragmentShader, vertexShader);

  setShadersAttributes(shaderProgram, posAttrib, colAttrib);
  return;
};

double frand_a_b(double a, double b) {
  return (rand() / (double)RAND_MAX) * (b - a) + a;
};

int main() {
  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit()) {
    return -1;
  }

  setBootstrapConfig();
  GLFWmonitor *monitorIsInFullScreen = NULL;
  if (isFullscreen == 1) {
    monitorIsInFullScreen = glfwGetPrimaryMonitor();
  }

  window = glfwCreateWindow(monitorRes.width, monitorRes.height, "OpenGL_test",
  monitorIsInFullScreen, NULL);
  printf("loadObject\n");
  if (!window) {
    glfwTerminate();
    return -1;
  }
  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  time_t startLoopTime, endLoopTime;
  double msBetweenFrame = getMsBetweenFrame();
  printf("msBetweenFrame: %lf\n", msBetweenFrame);

  GLuint vao;
  GLuint vbufferObj;
  GLuint shaderProgram;
  GLuint fragmentShader;
  GLuint vertexShader;
  GLint posAttrib;
  GLint colAttrib;

  Context_t openGL_program_ctx;
  printf("1\n");
  VertexArray_t_initArray(&openGL_program_ctx.VertexArray_s, 0);
  printf("2\n");
  VertexArray_t_push(&openGL_program_ctx.VertexArray_s, 0.0f);
  VertexArray_t_push(&openGL_program_ctx.VertexArray_s, 0.5f);
  VertexArray_t_push(&openGL_program_ctx.VertexArray_s, 1.0f);
  VertexArray_t_push(&openGL_program_ctx.VertexArray_s, 0.0f);
  VertexArray_t_push(&openGL_program_ctx.VertexArray_s, 0.0f);
  printf("3\n");
  printf("wtf 666: %f\n", openGL_program_ctx.VertexArray_s.array[2]);
  VertexArray_t_push(&openGL_program_ctx.VertexArray_s, 0.5f);
  VertexArray_t_push(&openGL_program_ctx.VertexArray_s, -0.5f);
  VertexArray_t_push(&openGL_program_ctx.VertexArray_s, 0.0f);
  VertexArray_t_push(&openGL_program_ctx.VertexArray_s, 1.0f);
  VertexArray_t_push(&openGL_program_ctx.VertexArray_s, 0.0f);
  printf("4\n");
  VertexArray_t_push(&openGL_program_ctx.VertexArray_s, -0.5f);
  VertexArray_t_push(&openGL_program_ctx.VertexArray_s, -0.5f);
  VertexArray_t_push(&openGL_program_ctx.VertexArray_s, 0.0f);
  VertexArray_t_push(&openGL_program_ctx.VertexArray_s, 0.0f);
  VertexArray_t_push(&openGL_program_ctx.VertexArray_s, 1.0f);
  printf("5\n");
  ArrayOfVertex_t_initArray(&openGL_program_ctx.ArrayOfVertex_s, 0);
  printf("6\n");
  ArrayOfVertex_t_push(&openGL_program_ctx.ArrayOfVertex_s, &openGL_program_ctx.VertexArray_s);
  printf("7\n");
  printf("wtf 666: %f\n", openGL_program_ctx.ArrayOfVertex_s.VertexArray_s[0].array[2]);
  VertexArray_t_freeIt(&openGL_program_ctx.VertexArray_s);
  printf("8\n");

  //printf("wtf: %f\n", openGL_program_ctx.ArrayOfVertex_s[0].VertexArray_s.array[2]);


  loadObject(&vao, &vbufferObj, &shaderProgram, &fragmentShader, &vertexShader,
             &posAttrib, &colAttrib, &openGL_program_ctx);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    startLoopTime = time(NULL);
    /*printf("currentTime with glfw: %lf\n", currentTime);*/

    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);

    // Draw a triangle from the 3 vertices
    glDrawArrays(GL_TRIANGLES, 0, 3);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    endLoopTime = time(NULL);

    Sleep(80 - difftime(endLoopTime, startLoopTime));

    /* Poll for and process events */
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
  }

  glDeleteProgram(shaderProgram);
  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);

  glDeleteBuffers(1, &vbufferObj);

  glDeleteVertexArrays(1, &vao);

  glfwTerminate();
  return 0;
};
