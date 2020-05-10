#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "includes/glad/glad.h"

#include <GLFW/glfw3.h>
#include <cglm/call.h>

#include "includes/include.h"

#include "src/objectManagement/includes/opperation.h"
#include "src/objectManagement/includes/constructor.h"
#include "src/window/includes/windowManager.h"
#include "src/shadersManagement/includes/shadersManager.h"
#include "src/vertexManagement/includes/vertexs.h"
#include "src/camera/includes/cameraManager.h"
#include "src/texturesManagement/includes/texturesManagement.h"
#include "src/inputManagement/includes/bindInputCallback.h"

#include <sys/time.h>

ScreenRes monitorRes;


void moveCamera(Context_t *openGL_program_ctx){
  openGL_program_ctx -> eye[0] = 8.0f;
  openGL_program_ctx -> eye[1] = 8.0f;
  openGL_program_ctx -> eye[2] = 2.0f;
}


void getCenter(vec3 *center, GLFWwindow* window){
  double xpos = 0.0;
  double ypos = 0.0;
  glfwGetCursorPos(window,	&xpos,	&ypos);
  /*
  printf("xpos %lf\n", xpos);
  printf("ypos %lf\n", ypos);
  */

  *center[0] = (float)xpos;
  *center[1] = (float)ypos;
  return;
 }

void setBootstrapConfig(void) {
  glfwSetErrorCallback(error_callback);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  glfwWindowHint(GLFW_DEPTH_BITS, 24);
  glfwWindowHint(GLFW_STENCIL_BITS, 8);
  return;
};

void setObjectRenderingConfig(void){
  glEnable(GL_DEPTH_TEST);
}

void loadObject(Context_t *openGL_program_ctx) {

  uploadVertexOntoTheGPU(openGL_program_ctx);
  loadShaders(&openGL_program_ctx -> shaderProgram, &openGL_program_ctx -> fragmentShader, &openGL_program_ctx -> vertexShader);
  setShadersAttributes(openGL_program_ctx);

  getTexture(openGL_program_ctx);
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
void drawPlaneSurface(Context_t *ctx){
//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    //start it
    glEnable(GL_STENCIL_TEST);

        // Draw floor
        glStencilFunc(GL_ALWAYS, 1, 0xFF); // Set any stencil to 1
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glStencilMask(0xFF); // Write to stencil buffer
        glDepthMask(GL_FALSE); // Don't write to depth buffer
        glClear(GL_STENCIL_BUFFER_BIT); // Clear stencil buffer (0 by default)

        glDrawArrays(GL_TRIANGLES, 36, 6);

        // Draw cube reflection
        glStencilFunc(GL_EQUAL, 1, 0xFF); // Pass test if stencil value is 1
        glStencilMask(0x00); // Don't write anything to stencil buffer
        glDepthMask(GL_TRUE); // Write to depth buffer

        vec3 translateVec = {0, 0, -1};
        vec3 scaleVec = {1, 1, -1};
        glm_translate(ctx -> position_model_mat, translateVec);
        glm_scale(ctx -> position_model_mat, scaleVec);
        glUniformMatrix4fv(ctx -> uniModel, 1, GL_FALSE, (float *)ctx -> position_model_mat);

        glUniform3f(ctx -> uniColor, 0.3f, 0.3f, 0.3f);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glUniform3f(ctx -> uniColor, 1.0f, 1.0f, 1.0f);

    //end it
    glDisable(GL_STENCIL_TEST);

    glm_translate(ctx -> position_model_mat, translateVec);
    glm_scale(ctx -> position_model_mat, scaleVec);
};

void checkFrameBufferStatus(){
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
    printf("framebuffer is complete\n");
  }else{
    printf("framebuffer is not complete\n");
  }
};

int main(void) {
  //TODO: ADD A LOAD CONF HERE cause it's annoying to recompile just for a conf param lol

  int err;
  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit()) {
    return -1;
  }

  setWindowProperties(&monitorRes);
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

  setBindingCallback(window);

  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("can't load glad\n");

    glfwTerminate();
    return -1;
  }

  /*
  // Define the viewport dimensions
  glViewport(0, 0, 800, 600);
  */

  setObjectRenderingConfig();

  time_t startLoopTime, endLoopTime;
  double msBetweenFrame = getMsBetweenFrame();
  printf("msBetweenFrame: %lf\n", msBetweenFrame);

  Context_t openGL_program_ctx;

  openGL_program_ctx.ScreenRes = monitorRes;

  //Set a reference to the structure so we can use it wherever we are as long we can have window
  glfwSetWindowUserPointer(window, &openGL_program_ctx);


  getVertexs(&openGL_program_ctx);

  ArrayOfVertex_t_initArray(&openGL_program_ctx.ArrayOfVertex_s, 0);
  //Add vertex array into the context structure
  ArrayOfVertex_t_push(&openGL_program_ctx.ArrayOfVertex_s, &openGL_program_ctx.VertexArray_s);
  //Free the temp array
  VertexArray_t_freeIt(&openGL_program_ctx.VertexArray_s);

  loadObject(&openGL_program_ctx);

  while ((err = glGetError()) != GL_NO_ERROR) {
    printf("error when loading the object OpenGL error: %d \n", err);
  }

  init_mat4_with_GLM_MAT4_IDENTITY_INIT(openGL_program_ctx.position_model_mat);
  print_mat4(openGL_program_ctx.position_model_mat, 0);

  //clear console
  //system("cls");


  openGL_program_ctx.eye[0] = 8.0f;
  openGL_program_ctx.eye[1] = 8.0f;
  openGL_program_ctx.eye[2] = 2.0f;

  openGL_program_ctx.center[0] = 0.0f;
  openGL_program_ctx.center[1] = 0.0f;
  openGL_program_ctx.center[2] = 0.0f;

  openGL_program_ctx.up[0] = 0.0f;
  openGL_program_ctx.up[1] = 0.0f;
  openGL_program_ctx.up[2] = 1.0f;

  glm_lookat(openGL_program_ctx.eye, openGL_program_ctx.center, openGL_program_ctx.up, openGL_program_ctx.view);
  glUniformMatrix4fv(openGL_program_ctx.uniView, 1, GL_FALSE, (float *)openGL_program_ctx.view);

  mat4 proj;
  glmc_perspective(glm_rad(45.0f), (float)monitorRes.width / (float)monitorRes.height, 1.0f, 50.0f, proj);


  glUniformMatrix4fv(openGL_program_ctx.uniProj, 1, GL_FALSE, (float *)proj);

  checkFrameBufferStatus();

  float rad = glm_rad(5.0f);
  vec3 normalvec3 = {0.0f, 0.0f, 1.0f};


  while ((err = glGetError()) != GL_NO_ERROR) {
    printf("init process got OpenGL error: %d \n", err);
  }

  vec3 vec3Array[] = {
   {2, 0, 0}, {0, 2, 0}, {0, 0, 2}, {0, 0, -4},
   {0, -2, 0}, {0, -2, 0}, {0, 0, 2}, {0, 0, 2},
   {0, 2, 0}, {-2, 0, -2}, {2, 0, 0}, {0, 2, 0},
   {0, 0, 2}, {0, 0, -4}, {0, -2, 0}, {0, -2, 0},
   {0, 0, 2}, {0, 0, 2}, {0, 2, 0}, {-2, 2, -2},
   {0, -4, 0}, {0, 0, 2}, {0, 2, 0}, {0, 2, 0},
   {0, 0, -4}, {0, -2, 0}, {0, -2, 0}, {0, 2, 2},
   {-2, 0, 0}, {0, 0, 2}, {0, 0, -4}, {0, 2, 0},
   {0, 0, 2}, {0, 0, 2}, {0, -4, 0}, {0, 0, -2},
   {0, 0, -2}, {2, 2, 2}
  };

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    startLoopTime = time(NULL);
    /*printf("currentTime with glfw: %lf\n", currentTime);*/

    /* Clear the screen to white */
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*glmc_rotate(openGL_program_ctx.position_model_mat, rad, normalvec3);*/
    /*glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);*/

    /* Draw a rectangle from the 2 triangles using 6 indices */
    /*glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);*/

    for (size_t i = 0; i < 38; i++) {
     glDrawArrays(GL_TRIANGLES, 0, 36);

     glm_translate(openGL_program_ctx.position_model_mat, vec3Array[i]);
     glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);
    }
    /*
    printf("before\n");
    print_mat3(&openGL_program_ctx.center, 0);
    getCenter(&openGL_program_ctx.center, window);
    printf("after\n");
    print_mat3(&openGL_program_ctx.center, 0);
    glm_lookat(openGL_program_ctx.eye, openGL_program_ctx.center, openGL_program_ctx.up, openGL_program_ctx.view);
    glUniformMatrix4fv(openGL_program_ctx.uniView, 1, GL_FALSE, (float *)openGL_program_ctx.view);

    */
    /*drawPlaneSurface(&openGL_program_ctx);*/

    while ((err = glGetError()) != GL_NO_ERROR) {
      printf("main loop got OpenGL error: %d \n", err);
    }

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    //getchar();

    /* Poll for and process events */
    glfwPollEvents();


    endLoopTime = time(NULL);
    /*
    printf("startLoopTime: %I64d\n", startLoopTime);
    printf("endLoopTime: %I64d\n", endLoopTime);
    */
    //printf("difftime %lf\n", difftime(endLoopTime, startLoopTime));
    Sleep((1000/framePerSec) - difftime(endLoopTime, startLoopTime));

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
