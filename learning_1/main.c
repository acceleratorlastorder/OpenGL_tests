#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "include/glad/glad.h"

#include <GLFW/glfw3.h>

#include "include/include.h"

#define isFullscreen 0
#define framePerSec 30.0

// Window dimensions
const GLuint width = 1280, height = 720;

double getMsBetweenFrame() { return (1 / framePerSec); }

void readFile(char *charArray, char *filePath) {
  int c;
  FILE *file;
  file = fopen(filePath, "r");
  if (file) {
    int i = 0;
    while ((c = getc(file)) != EOF) {
      charArray[i] = c;
      // putchar(c);
      i++;
    }
    fclose(file);
    charArray[i - 1] = '\0';
  }
}

/**
 * [Compiling the given shader onto the GPU]
 */
void compileShader(char *vertexShaderSource, GLuint *shaderProgram) {
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, (const GLchar **)(&vertexShaderSource), NULL);
  glCompileShader(vertexShader);

  GLint status;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

  if (status == GL_TRUE) {
    printf("vertex shader is corectly loaded\n");
  } else {
    printf("vertex shader got problem\n");
  }

  char buffer[512];
  glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
  printf("log for the vertex shader: %s\n", buffer);
  glAttachShader(*shaderProgram, vertexShader);
}

/**
 * [Compiling the given fragment shader onto the GPU]
 */
void compileFragmentShader(char *fragmentShaderSource, GLuint *shaderProgram) {
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, (const GLchar **)(&fragmentShaderSource),
                 NULL);
  glCompileShader(fragmentShader);

  GLint status;
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);

  if (status == GL_TRUE) {
    printf("fragment shader is corectly loaded\n");
  } else {
    printf("fragment shader got problem\n");
  }
  char buffer[512];
  glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
  printf("log for fragment the shader: %s\n", buffer);
  glAttachShader(*shaderProgram, fragmentShader);
}

void uploadVertexOntoTheGPU() {
  GLfloat vertices[] = {
      0.0f,  0.5f,  // Vertex 1 (X, Y)
      0.5f,  -0.5f, // Vertex 2 (X, Y)
      -0.5f, -0.5f  // Vertex 3 (X, Y)
  };
  GLuint vbufferObj;
  glGenBuffers(1, &vbufferObj);
  printf("vbufferObj: %d\n", vbufferObj);

  glBindBuffer(GL_ARRAY_BUFFER, vbufferObj); // BIND current vbo as array buffer
                                             // and make it current active
                                             // arrayBuff
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  printf("vbufferObj finished\n");
}

GLuint loadShaders() {
  char fileContent[666];
  char *filePath = "include/shaders/vertexShader.glsl";

  // get shader
  //printf("filePath: %s\n", filePath);
  readFile(fileContent, filePath);
  GLuint shaderProgram = glCreateProgram();
  compileShader(fileContent, &shaderProgram);

  // reset string
  fillStringWithNull(fileContent);

  // get fragment shader
  filePath = "include/shaders/fragmentShader.frag";
  //printf("fileContent: %s\n", filePath);
  readFile(fileContent, filePath);
  compileFragmentShader(fileContent, &shaderProgram);

  // remove string
  removeStringFromMemory(fileContent);

  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

  return shaderProgram;
}

void loadObject(void) {
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  uploadVertexOntoTheGPU();
  GLuint shaderProgram = loadShaders();

  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(posAttrib);


}

int main() {

  time_t startLoopTime, endLoopTime;
  double msBetweenFrame = getMsBetweenFrame();
  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit()) {

    return -1;
  }

  GLFWmonitor *monitorIsInFullScreen = NULL;

  if (isFullscreen == 1) {
    monitorIsInFullScreen = glfwGetPrimaryMonitor();
  }

  glfwSetErrorCallback(error_callback);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  window = glfwCreateWindow(width, height, "OpenGL", monitorIsInFullScreen, NULL);

  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  loadObject();
  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */

    glEnable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT);

    //startLoopTime = time(NULL);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);
    //endLoopTime = time(NULL);
    // printf("endLoopTime: %lf, startLoopTime: %lf\n", endLoopTime,
    // startLoopTime);
    // Sleep(msBetweenFrame - difftime(endLoopTime, startLoopTime));
    // Sleep(20);
    /* Poll for and process events */
    glfwPollEvents();
    /*if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }*/
  }

  glfwTerminate();
  return 0;
}
