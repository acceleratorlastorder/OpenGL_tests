#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "includes/glad/glad.h"

#include <GLFW/glfw3.h>
#include <cglm/call.h>

#include "includes/include.h"

#include "src/objectManagement/includes/opperation.h"
#include "src/objectManagement/includes/constructor.h"
#include "src/shadersManagement/includes/shadersManager.h"
#include "src/vertexManagement/includes/vertexs.h"
#include "src/texturesManagement/includes/texturesManagement.h"

screenRes monitorRes = {.width = 1200, .height = 800};

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (action == GLFW_PRESS) {
    Context_t* openGL_ctx = (Context_t *)glfwGetWindowUserPointer(window);
    if (key == GLFW_KEY_ESCAPE){
      glfwSetWindowShouldClose(window, GLFW_TRUE);
    }else if (key == GLFW_KEY_F3) {
     reloadShaders(openGL_ctx);
     //clearScreen();
    }else if(key == GLFW_KEY_F1){
     /*moving edge test*/
     printf("openGL_program_ctx.ArrayOfVertex_s.VertexArray_s[0].array[1]: %f\n", openGL_ctx->ArrayOfVertex_s.VertexArray_s[0].array[1]);
     openGL_ctx->ArrayOfVertex_s.VertexArray_s[0].array[1] -= 0.1;
     printf("after array[1]: %f\n", openGL_ctx->ArrayOfVertex_s.VertexArray_s[0].array[1]);
     glBufferSubData(GL_ARRAY_BUFFER, 0, openGL_ctx->ArrayOfVertex_s.VertexArray_s[0].sizeOfItems, openGL_ctx->ArrayOfVertex_s.VertexArray_s[0].array);
    }else if(key == GLFW_KEY_F2){
     /*moving edge test*/
     printf("openGL_program_ctx.ArrayOfVertex_s.VertexArray_s[0].array[1]: %f\n", openGL_ctx->ArrayOfVertex_s.VertexArray_s[0].array[1]);
     openGL_ctx->ArrayOfVertex_s.VertexArray_s[0].array[1] += 0.1;
     printf("after array[1]: %f\n", openGL_ctx->ArrayOfVertex_s.VertexArray_s[0].array[1]);
     glBufferSubData(GL_ARRAY_BUFFER, 0, openGL_ctx->ArrayOfVertex_s.VertexArray_s[0].sizeOfItems, openGL_ctx->ArrayOfVertex_s.VertexArray_s[0].array);
    }else if(key == GLFW_KEY_F5){
     /*moving edge test*/
     printf("openGL_program_ctx.ArrayOfVertex_s.VertexArray_s[0].array[1]: %f\n", openGL_ctx->ArrayOfVertex_s.VertexArray_s[0].array[1]);
     openGL_ctx->ArrayOfVertex_s.VertexArray_s[0].array[1] -= 0.1;
     printf("after array[1]: %f\n", openGL_ctx->ArrayOfVertex_s.VertexArray_s[0].array[0]);
     glBufferSubData(GL_ARRAY_BUFFER, 0, openGL_ctx->ArrayOfVertex_s.VertexArray_s[0].sizeOfItems, openGL_ctx->ArrayOfVertex_s.VertexArray_s[0].array);
    }else if(key == GLFW_KEY_F6){
     /*moving edge test*/
     printf("openGL_program_ctx.ArrayOfVertex_s.VertexArray_s[0].array[1]: %f\n", openGL_ctx->ArrayOfVertex_s.VertexArray_s[0].array[1]);
     openGL_ctx->ArrayOfVertex_s.VertexArray_s[0].array[1] += 0.1;
     printf("after array[1]: %f\n", openGL_ctx->ArrayOfVertex_s.VertexArray_s[0].array[0]);
     glBufferSubData(GL_ARRAY_BUFFER, 0, openGL_ctx->ArrayOfVertex_s.VertexArray_s[0].sizeOfItems, openGL_ctx->ArrayOfVertex_s.VertexArray_s[0].array);
    }
  }
}

void setBootstrapConfig(void) {
  glfwSetErrorCallback(error_callback);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  return;
};

void setObjectRenderingConfig(void){
  glEnable(GL_DEPTH_TEST);
}

void loadObject(Context_t *openGL_program_ctx) {
  getTexture(openGL_program_ctx);

  uploadVertexOntoTheGPU(openGL_program_ctx);
  loadShaders(&openGL_program_ctx -> shaderProgram, &openGL_program_ctx -> fragmentShader, &openGL_program_ctx -> vertexShader);
  setShadersAttributes(openGL_program_ctx);
  return;
};

double frand_a_b(double a, double b) {
  return (rand() / (double)RAND_MAX) * (b - a) + a;
};
/*
  clock counter helper
static int inline SpinALot(int spinCount)
{
    __m128 x = _mm_setzero_ps();
    for(int i=0; i<spinCount; i++) {
        x = _mm_add_ps(x,_mm_set1_ps(1.0f));
    }
    return _mm_cvt_ss2si(x);
}
*/

int main() {
  //TODO: ADD A LOAD CONF HERE cause it's annoying to recompile just for a conf param lol

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

  window = glfwCreateWindow(monitorRes.width, monitorRes.height, "OpenGL_test", monitorIsInFullScreen, NULL);
  printf("loadObject\n");
  if (!window) {
    glfwTerminate();
    return -1;
  }
  glfwSetKeyCallback(window, key_callback);

  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  setObjectRenderingConfig();

  time_t startLoopTime, endLoopTime;
  double msBetweenFrame = getMsBetweenFrame();
  printf("msBetweenFrame: %lf\n", msBetweenFrame);

  Context_t openGL_program_ctx;

  //Set a reference to the structure so we can use it wherever we are as long we can have window
  glfwSetWindowUserPointer(window, &openGL_program_ctx);


  getVertexs(&openGL_program_ctx);

  ArrayOfVertex_t_initArray(&openGL_program_ctx.ArrayOfVertex_s, 0);
  //Add vertex array into the context structure
  ArrayOfVertex_t_push(&openGL_program_ctx.ArrayOfVertex_s, &openGL_program_ctx.VertexArray_s);
  //Free the temp array
  VertexArray_t_freeIt(&openGL_program_ctx.VertexArray_s);

  loadObject(&openGL_program_ctx);

  //TODO: change it for GLM_MAT4_IDENTITY_INIT
  init_mat4_with_GLM_MAT4_IDENTITY_INIT(openGL_program_ctx.position_mat);

  //clear console
  //system("cls");
  float rad = glm_rad(5.0f);
  vec3 normalvec3 = {0.0f, 0.0f, 1.0f};


  mat4 view;
  glm_mat4_print(view, stderr);
  vec3 eye = {1.2f, 1.2f, 1.2f};
  vec3 center = {0.0f, 0.0f, 0.0f};
  vec3 up = {0.0f, 0.0f, 1.0f};
  glm_lookat(eye, center, up, view);
  glm_mat4_print(view, stderr);

  GLint uniView = glGetUniformLocation(openGL_program_ctx.shaderProgram, "view");
  glUniformMatrix4fv(uniView, 1, GL_FALSE, (float *)view);


  mat4 proj;
  glm_perspective(glm_rad(45.0f), 800.0f / 600.0f, 1.0f, 10.0f, proj);

  GLint uniProj = glGetUniformLocation(openGL_program_ctx.shaderProgram, "proj");
  glUniformMatrix4fv(uniProj, 1, GL_FALSE, (float *)proj);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {

    /* Render here */
    startLoopTime = time(NULL);
    /*printf("currentTime with glfw: %lf\n", currentTime);*/

    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm_rotate(openGL_program_ctx.position_mat, rad, normalvec3);
    glUniformMatrix4fv(openGL_program_ctx.uniTrans, 1, GL_FALSE, (float *)openGL_program_ctx.position_mat);

    // Draw a rectangle from the 2 triangles using 6 indices
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    endLoopTime = time(NULL);
    /*
    printf("startLoopTime: %I64d\n", startLoopTime);
    printf("endLoopTime: %I64d\n", endLoopTime);
    */
    Sleep((1000/24) - difftime(endLoopTime, startLoopTime));

    /* Poll for and process events */
    glfwPollEvents();
  }
  glDeleteTextures(1, &openGL_program_ctx.textureID);

  glDeleteProgram(openGL_program_ctx.shaderProgram);
  glDeleteShader(openGL_program_ctx.fragmentShader);
  glDeleteShader(openGL_program_ctx.vertexShader);

  //glDeleteBuffers(1, &openGL_program_ctx.ebo);
  glDeleteBuffers(1, &openGL_program_ctx.vbufferObj);

  glDeleteVertexArrays(1, &openGL_program_ctx.vao);

  glfwTerminate();
  return 0;
};
