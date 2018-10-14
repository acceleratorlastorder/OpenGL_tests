#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <sys/time.h>

#include "includes/glad/glad.h"

#include <GLFW/glfw3.h>
#include <cglm/call.h>

#include "includes/include.h"

#include "src/objectManagement/includes/opperation.h"
#include "src/objectManagement/includes/constructor.h"
#include "src/shadersManagement/includes/shadersManager.h"
#include "src/vertexManagement/includes/vertexs.h"
#include "src/texturesManagement/includes/texturesManagement.h"



#include "src/tests/includes/test.h"


/*Default param*/
int screenWidth = 800;
int screenHeight = 600;

void moveCamera(Context_t *openGL_program_ctx){
  openGL_program_ctx -> eye[0] = 8.0f;
  openGL_program_ctx -> eye[1] = 8.0f;
  openGL_program_ctx -> eye[2] = 2.0f;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
  printf("yooo key: %d, scancode: %d, action: %d, mods: %d\n", key, scancode, action, mods);
  if (action == GLFW_PRESS || action == GLFW_REPEAT) {
    if (action == GLFW_PRESS) {
      if (key == GLFW_KEY_ESCAPE){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
      }else if (key == GLFW_KEY_F3) {
        Context_t* openGL_ctx = (Context_t *)glfwGetWindowUserPointer(window);
        reloadShaders(openGL_ctx);
        //clearScreen();
      }else if (key == GLFW_KEY_F5) {
        Context_t* openGL_ctx = (Context_t *)glfwGetWindowUserPointer(window);
        static int framebufferswitchStatus = 0;
        if (framebufferswitchStatus == 0) {
          framebufferswitchStatus = 1;
          glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }else if(framebufferswitchStatus == 1){
          framebufferswitchStatus = 0;
          glBindFramebuffer(GL_FRAMEBUFFER, openGL_ctx -> frameBuffer);
        }
      }
    }
    if(key == GLFW_KEY_RIGHT || key == GLFW_KEY_LEFT || key == GLFW_KEY_UP || key == GLFW_KEY_DOWN){
      Context_t* openGL_ctx = (Context_t *)glfwGetWindowUserPointer(window);
      if(key == GLFW_KEY_RIGHT){
        openGL_ctx -> cameraParam.eye[0] -= 1.0f;
      }
      if(key == GLFW_KEY_LEFT){
        openGL_ctx -> cameraParam.eye[0] += 1.0f;
      }
      if(key == GLFW_KEY_UP){
        openGL_ctx -> cameraParam.eye[1] -= 1.0f;
      }
      if(key == GLFW_KEY_DOWN){
        openGL_ctx -> cameraParam.eye[1] += 1.0f;
      }

      glm_lookat(openGL_ctx -> cameraParam.eye, openGL_ctx -> cameraParam.center,
            openGL_ctx -> cameraParam.up, openGL_ctx -> cameraParam.view);
      glUniformMatrix4fv(openGL_ctx -> uniView, 1, GL_FALSE, (float *)openGL_ctx -> cameraParam.view);
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

  Context_t openGL_program_ctx;

  openGL_program_ctx.monitorRes.width = screenWidth;
  openGL_program_ctx.monitorRes.height = screenHeight;

  /* Initialize the library */
  if (!glfwInit()) {
    return -1;
  }

  setBootstrapConfig();
  GLFWmonitor *monitorIsInFullScreen = NULL;
  if (isFullscreen == 1) {
    monitorIsInFullScreen = glfwGetPrimaryMonitor();
  }

  char *windowTitle = "OpenGL_test FPS: ";

  window = glfwCreateWindow(openGL_program_ctx.monitorRes.width, openGL_program_ctx.monitorRes.height, windowTitle, monitorIsInFullScreen, NULL);
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


  //Set a reference to the structure so we can use it wherever we are as long we can have window
  glfwSetWindowUserPointer(window, &openGL_program_ctx);


  getVertexs(&openGL_program_ctx);

  ArrayOfVertex_t_initArray(&openGL_program_ctx.ArrayOfVertex_s, 0);
  //Add vertex array into the context structure
  ArrayOfVertex_t_push(&openGL_program_ctx.ArrayOfVertex_s, &openGL_program_ctx.VertexArray_s);
  //Free the temp array
  VertexArray_t_freeIt(&openGL_program_ctx.VertexArray_s);

  loadObject(&openGL_program_ctx);


  glGenFramebuffers(1, &openGL_program_ctx.frameBuffer);

  glBindFramebuffer(GL_FRAMEBUFFER, openGL_program_ctx.frameBuffer);


  checkFrameBufferStatus();
  /*FRAMEBUFER START*/

  GLuint texColorBuffer;
  glGenTextures(1, &texColorBuffer);
  glBindTexture(GL_TEXTURE_2D, texColorBuffer);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, openGL_program_ctx.monitorRes.width, openGL_program_ctx.monitorRes.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

  GLuint rboDepthStencil;
  glGenRenderbuffers(1, &rboDepthStencil);
  glBindRenderbuffer(GL_RENDERBUFFER, rboDepthStencil);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, openGL_program_ctx.monitorRes.width, openGL_program_ctx.monitorRes.height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboDepthStencil);

  /*FRAME BUFER END*/


  while ((err = glGetError()) != GL_NO_ERROR) {
    printf("error when loading the object OpenGL error: %d \n", err);
  }

  init_mat4_with_GLM_MAT4_IDENTITY_INIT(openGL_program_ctx.position_model_mat);
  print_mat4(openGL_program_ctx.position_model_mat, 0);

  //clear console
  //system("cls");


  openGL_program_ctx.cameraParam.eye[0] = 8.0f;
  openGL_program_ctx.cameraParam.eye[1] = 8.0f;
  openGL_program_ctx.cameraParam.eye[2] = 2.0f;

  openGL_program_ctx.cameraParam.center[0] = 0.0f;
  openGL_program_ctx.cameraParam.center[1] = 0.0f;
  openGL_program_ctx.cameraParam.center[2] = 0.0f;

  openGL_program_ctx.cameraParam.up[0] = 0.0f;
  openGL_program_ctx.cameraParam.up[1] = 0.0f;
  openGL_program_ctx.cameraParam.up[2] = 1.0f;

  glm_lookat(openGL_program_ctx.eye, openGL_program_ctx.cameraParam.center,
      openGL_program_ctx.cameraParam.up, openGL_program_ctx.cameraParam.view);
  glUniformMatrix4fv(openGL_program_ctx.uniView, 1, GL_FALSE, (float *)openGL_program_ctx.cameraParam.view);


  mat4 proj;
  glmc_perspective(glm_rad(45.0f), (float)openGL_program_ctx.monitorRes.width / (float)openGL_program_ctx.monitorRes.height, 1.0f, 50.0f, proj);
  glUniformMatrix4fv(openGL_program_ctx.uniProj, 1, GL_FALSE, (float *)proj);


  /*
  float rad = glm_rad(5.0f);
  vec3 normalvec3 = {0.0f, 0.0f, 1.0f};
  */

  while ((err = glGetError()) != GL_NO_ERROR) {
    printf("init process got OpenGL error: %d \n", err);
  }

  glUseProgram(openGL_program_ctx.shaderProgram);


  initTest();

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    startLoopTime = time(NULL);
    /*printf("currentTime with glfw: %lf\n", currentTime);*/

    // Clear the screen to white
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glmc_rotate(openGL_program_ctx.position_model_mat, rad, normalvec3);
    //glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);

    // Draw a rectangle from the 2 triangles using 6 indices
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glDrawArrays(GL_TRIANGLES, 0, 36);



    glm_translate(openGL_program_ctx.position_model_mat, (vec3){2, 0, 0});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);

    glDrawArrays(GL_TRIANGLES, 0, 36);



    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 2, 0});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);

    glDrawArrays(GL_TRIANGLES, 0, 36);



    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 0, 2});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);

    glDrawArrays(GL_TRIANGLES, 0, 36);



    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 0, -4});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);

    glDrawArrays(GL_TRIANGLES, 0, 36);



    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, -2, 0});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);

    glDrawArrays(GL_TRIANGLES, 0, 36);



    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, -2, 0});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);

    glDrawArrays(GL_TRIANGLES, 0, 36);



    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 0, 2});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);

    glDrawArrays(GL_TRIANGLES, 0, 36);



    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 0, 2});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);

    glDrawArrays(GL_TRIANGLES, 0, 36);



    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 2, 0});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);

    glDrawArrays(GL_TRIANGLES, 0, 36);






    glm_translate(openGL_program_ctx.position_model_mat, (vec3){-2, 0, -2});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);






    glm_translate(openGL_program_ctx.position_model_mat, (vec3){2, 0, 0});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);

    glDrawArrays(GL_TRIANGLES, 0, 36);



    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 2, 0});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);

    glDrawArrays(GL_TRIANGLES, 0, 36);



    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 0, 2});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);

    glDrawArrays(GL_TRIANGLES, 0, 36);



    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 0, -4});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);

    glDrawArrays(GL_TRIANGLES, 0, 36);



    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, -2, 0});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);

    glDrawArrays(GL_TRIANGLES, 0, 36);



    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, -2, 0});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);

    glDrawArrays(GL_TRIANGLES, 0, 36);



    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 0, 2});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);

    glDrawArrays(GL_TRIANGLES, 0, 36);



    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 0, 2});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);

    glDrawArrays(GL_TRIANGLES, 0, 36);



    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 2, 0});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);

    glDrawArrays(GL_TRIANGLES, 0, 36);




    /**/

    glm_translate(openGL_program_ctx.position_model_mat, (vec3){-2, 2, -2});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);

    glDrawArrays(GL_TRIANGLES, 0, 36);



    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, -4, 0});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);

    glDrawArrays(GL_TRIANGLES, 0, 36);



    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 0, 2});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);

    glDrawArrays(GL_TRIANGLES, 0, 36);


    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 2, 0});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);


    glDrawArrays(GL_TRIANGLES, 0, 36);



    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 2, 0});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);


    glDrawArrays(GL_TRIANGLES, 0, 36);


    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 0, -4});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);


    glDrawArrays(GL_TRIANGLES, 0, 36);


    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, -2, 0});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);


    glDrawArrays(GL_TRIANGLES, 0, 36);


    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, -2, 0});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);


    glDrawArrays(GL_TRIANGLES, 0, 36);


    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 2, 2});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);



    glm_translate(openGL_program_ctx.position_model_mat, (vec3){-2, 0, 0});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);


    glDrawArrays(GL_TRIANGLES, 0, 36);


    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 0, 2});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);


    glDrawArrays(GL_TRIANGLES, 0, 36);


    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 0, -4});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);


    glDrawArrays(GL_TRIANGLES, 0, 36);


    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 2, 0});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);


    glDrawArrays(GL_TRIANGLES, 0, 36);



    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 0, 2});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);


    glDrawArrays(GL_TRIANGLES, 0, 36);


    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 0, 2});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);


    glDrawArrays(GL_TRIANGLES, 0, 36);


    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, -4, 0});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);


    glDrawArrays(GL_TRIANGLES, 0, 36);


    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 0, -2});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);


    glDrawArrays(GL_TRIANGLES, 0, 36);


    glm_translate(openGL_program_ctx.position_model_mat, (vec3){0, 0, -2});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);


    glDrawArrays(GL_TRIANGLES, 0, 36);


    glm_translate(openGL_program_ctx.position_model_mat, (vec3){2, 2, 2});
    glUniformMatrix4fv(openGL_program_ctx.uniModel, 1, GL_FALSE, (float *)openGL_program_ctx.position_model_mat);


    //drawPlaneSurface(&openGL_program_ctx);

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
    char title[600] = "";
    sprintf(title, "opengGL test FPS: %f", (float)(1000/((float)(1000/60) - (float)difftime(endLoopTime, startLoopTime))));
    glfwSetWindowTitle(window,	title);
    Sleep((1000/60) - difftime(endLoopTime, startLoopTime));
  }

  glDeleteTextures(1, &openGL_program_ctx.textureID);

  glDeleteProgram(openGL_program_ctx.shaderProgram);
  glDeleteShader(openGL_program_ctx.fragmentShader);
  glDeleteShader(openGL_program_ctx.vertexShader);

  glDeleteFramebuffers(1, &openGL_program_ctx.frameBuffer);

  //glDeleteBuffers(1, &openGL_program_ctx.ebo);
  glDeleteBuffers(1, &openGL_program_ctx.vbufferObj);

  glDeleteVertexArrays(1, &openGL_program_ctx.vao);

  glfwTerminate();

  return 0;
};
