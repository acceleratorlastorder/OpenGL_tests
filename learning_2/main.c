#include <math.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "include/glad/glad.h"

#include <GLFW/glfw3.h>

#include "include/include.h"

// Window dimensions
const GLuint width = 800, height = 600;

void loadObject(GLuint *vao, GLuint *vbufferObj, GLuint *shaderProgram,
                GLuint *fragmentShader, GLuint *vertexShader, GLint *posAttrib,
                GLint *colAttrib) {
  glGenVertexArrays(1, vao);
  glBindVertexArray(*vao);

  uploadVertexOntoTheGPU(vbufferObj);
  loadShaders(shaderProgram, fragmentShader, vertexShader);

  setShadersAttributes(shaderProgram, posAttrib, colAttrib);
}

double frand_a_b(double a, double b) {
  return (rand() / (double)RAND_MAX) * (b - a) + a;
}

int main() {

  time_t startLoopTime, endLoopTime;
  double msBetweenFrame = getMsBetweenFrame();
  printf("msBetweenFrame: %lf\n", msBetweenFrame);
  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit()) {

    return -1;
  }

  GLFWmonitor *monitorIsInFullScreen = NULL;

  if (isFullscreen == 1) {
    monitorIsInFullScreen = glfwGetPrimaryMonitor();
  }

  setBootstrapConfig();

  window =
      glfwCreateWindow(width, height, "OpenGL", monitorIsInFullScreen, NULL);

  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  GLuint vao;
  GLuint vbufferObj;
  GLuint shaderProgram;
  GLuint fragmentShader;
  GLuint vertexShader;
  GLint posAttrib;
  GLint colAttrib;

  loadObject(&vao, &vbufferObj, &shaderProgram, &fragmentShader, &vertexShader,
             &posAttrib, &colAttrib);

  // GLint fragColor = glGetUniformLocation(shaderProgram, "fragColor");

  srand(time(NULL)); // initialisation de rand

  // double r = 0, g = 0, b = 0;
  // double increaseFactor = 0.001, decreaseFactor = 0.001;
  // int rHasreachOne = 0, gHasreachOne = 0, bHasreachOne = 0;
  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    startLoopTime = time(NULL);

    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a triangle from the 3 vertices
    glDrawArrays(GL_TRIANGLES, 0, 3);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

// glUniform3f(fragColor, r, g, b);
/*
if (rHasreachOne == 0) {
  r = sin(increaseFactor + r);
} else if (rHasreachOne == 1) {
  r -= sin(decreaseFactor - r);
}
if (gHasreachOne == 0) {
  g += tanh(increaseFactor + g);
} else if (gHasreachOne == 1) {
  g -= tanh(decreaseFactor + g);
}
if (bHasreachOne == 0) {
  b += cos(increaseFactor + b);
} else if (bHasreachOne == 1) {
  b -= cos(decreaseFactor - b);
}
if (r < 0) {
  rHasreachOne = 0;
} else if (r > 1) {
  rHasreachOne = 1;
}
if (g < 0) {
  gHasreachOne = 0;
} else if (g > 1) {
  gHasreachOne = 1;
}
if (b < 0) {
  bHasreachOne = 0;
} else if (b > 1) {
  bHasreachOne = 1;
}*/

#ifdef debugBuild
// printf("r: %f;\ng: %f;\nb: %f\n", r, g, b);
#endif
    endLoopTime = time(NULL);
    // printf("endLoopTime: %ld, startLoopTime: %ld\n", endLoopTime,
    // startLoopTime);
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
}
