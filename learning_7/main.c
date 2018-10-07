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

  #include <sys/time.h>

screenRes monitorRes = {.width = 800, .height = 600};

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
}


int main(void) {
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

  //Set a reference to the structure so we can use it wherever we are as long we can have window
  glfwSetWindowUserPointer(window, &openGL_program_ctx);


  getVertexs(&openGL_program_ctx);

  ArrayOfVertex_t_initArray(&openGL_program_ctx.ArrayOfVertex_s, 0);
  //Add vertex array into the context structure
  ArrayOfVertex_t_push(&openGL_program_ctx.ArrayOfVertex_s, &openGL_program_ctx.VertexArray_s);
  //Free the temp array
  VertexArray_t_freeIt(&openGL_program_ctx.VertexArray_s);

  loadObject(&openGL_program_ctx);

  init_mat4_with_GLM_MAT4_IDENTITY_INIT(openGL_program_ctx.position_model_mat);
  print_mat4(openGL_program_ctx.position_model_mat, 0);

  //clear console
  //system("cls");


  mat4 view;
  vec3 eye = {2.5f, 2.5f, 2.0f};
  vec3 center = {0.0f, 0.0f, 0.0f};
  vec3 up = {0.0f, 0.0f, 1.0f};
  glm_lookat(eye, center, up, view);

  print_mat4(view, 0);
  print_mat4_pretty_format(view);

  glUniformMatrix4fv(openGL_program_ctx.uniView, 1, GL_FALSE, (float *)view);

  mat4 proj;
  glmc_perspective(glm_rad(45.0f), (float)monitorRes.width / (float)monitorRes.height, 1.0f, 10.0f, proj);


  glUniformMatrix4fv(openGL_program_ctx.uniProj, 1, GL_FALSE, (float *)proj);



  float rad = glm_rad(5.0f);
  vec3 normalvec3 = {0.0f, 0.0f, 1.0f};

  int err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    printf("init process got OpenGL error: %d \n", err);
  }


  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    startLoopTime = time(NULL);
    /*printf("currentTime with glfw: %lf\n", currentTime);*/

    // Clear the screen to white
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glmc_rotate(openGL_program_ctx.position_model_mat, rad, normalvec3);
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);

    // Draw a rectangle from the 2 triangles using 6 indices
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    drawPlaneSurface(&openGL_program_ctx);

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
    Sleep((1000/60) - difftime(endLoopTime, startLoopTime));

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
