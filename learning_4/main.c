
#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "include/glad/glad.h"

#include <GLFW/glfw3.h>

#include "include/include.h"

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

void loadObject(Context_t *openGL_program_ctx) {

  glGenBuffers(1, &openGL_program_ctx -> ebo);
  uploadVertexOntoTheGPU(openGL_program_ctx);
  loadShaders(&openGL_program_ctx -> shaderProgram, &openGL_program_ctx -> fragmentShader, &openGL_program_ctx -> vertexShader);
  setShadersAttributes(&openGL_program_ctx -> shaderProgram, &openGL_program_ctx -> posAttrib, &openGL_program_ctx -> colAttrib);
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

  Context_t openGL_program_ctx;

  initVertexArray_t(&openGL_program_ctx.VertexArray_s, 0);

  openGL_program_ctx.VertexArray_s.push(&openGL_program_ctx.VertexArray_s, 0.0f);
  openGL_program_ctx.VertexArray_s.push(&openGL_program_ctx.VertexArray_s, 0.5f);
  openGL_program_ctx.VertexArray_s.push(&openGL_program_ctx.VertexArray_s, 1.0f);
  openGL_program_ctx.VertexArray_s.push(&openGL_program_ctx.VertexArray_s, 0.0f);
  openGL_program_ctx.VertexArray_s.push(&openGL_program_ctx.VertexArray_s, 0.0f);

  openGL_program_ctx.VertexArray_s.push(&openGL_program_ctx.VertexArray_s, 0.5f);
  openGL_program_ctx.VertexArray_s.push(&openGL_program_ctx.VertexArray_s, -0.5f);
  openGL_program_ctx.VertexArray_s.push(&openGL_program_ctx.VertexArray_s, 0.0f);
  openGL_program_ctx.VertexArray_s.push(&openGL_program_ctx.VertexArray_s, 1.0f);
  openGL_program_ctx.VertexArray_s.push(&openGL_program_ctx.VertexArray_s, 0.0f);

  openGL_program_ctx.VertexArray_s.push(&openGL_program_ctx.VertexArray_s, -0.5f);
  openGL_program_ctx.VertexArray_s.push(&openGL_program_ctx.VertexArray_s, -0.5f);
  openGL_program_ctx.VertexArray_s.push(&openGL_program_ctx.VertexArray_s, 0.0f);
  openGL_program_ctx.VertexArray_s.push(&openGL_program_ctx.VertexArray_s, 0.0f);
  openGL_program_ctx.VertexArray_s.push(&openGL_program_ctx.VertexArray_s, 1.0f);

  initArrayOfVertex_t(&openGL_program_ctx.ArrayOfVertex_s, 0);
  openGL_program_ctx.ArrayOfVertex_s.push(&openGL_program_ctx.ArrayOfVertex_s, &openGL_program_ctx.VertexArray_s);

  printf("wtf 666 666 666: %f\n", openGL_program_ctx.ArrayOfVertex_s.VertexArray_s[0] -> array);

  //printf("wtf: %f\n", openGL_program_ctx.ArrayOfVertex_s[0].VertexArray_s.array[2]);


  loadObject(&openGL_program_ctx);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    startLoopTime = time(NULL);
    /*printf("currentTime with glfw: %lf\n", currentTime);*/

    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);

    // Draw a triangle from the 3 vertices
    //glDrawArrays(GL_TRIANGLES, 0, 3);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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

  glDeleteProgram(openGL_program_ctx.shaderProgram);
  glDeleteShader(openGL_program_ctx.fragmentShader);
  glDeleteShader(openGL_program_ctx.vertexShader);

  glDeleteBuffers(1, &openGL_program_ctx.vbufferObj);

  glDeleteVertexArrays(1, &openGL_program_ctx.vao);

  glfwTerminate();
  return 0;
};
