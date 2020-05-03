#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "../../includes/glad/glad.h"
#include <GLFW/glfw3.h>
#include <cglm/call.h>


#include "../objectManagement/includes/constructor.h"
#include "../shadersManagement/includes/shadersManager.h"


static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
 /* sample to get the cursor pos outside of the callback
 double xpos, ypos;
 glfwGetCursorPos(window, &xpos, &ypos);
 */
 printf("cursor moved callback xpos: %f, ypos: %f\n", xpos, ypos);
}



static void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
 printf("yooo button: %d, action: %d, mods: %d\n", button, action, mods);
 if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
  Context_t* openGL_ctx = (Context_t *)glfwGetWindowUserPointer(window);
  printf("left !!!\n");
  /*getCenter(openGL_ctx -> center, window);*/


 }
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  printf("yooo key: %d, scancode: %d, action: %d, mods: %d\n", key, scancode, action, mods);
  if (action == GLFW_PRESS || action == GLFW_REPEAT) {
    if (action == GLFW_PRESS) {
      if (key == GLFW_KEY_ESCAPE){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
      }else if (key == GLFW_KEY_F3) {
        Context_t* openGL_ctx = (Context_t *)glfwGetWindowUserPointer(window);
        reloadShaders(openGL_ctx);
        //clearScreen();
      }
    }
    if(key == GLFW_KEY_RIGHT || key == GLFW_KEY_LEFT || key == GLFW_KEY_UP || key == GLFW_KEY_DOWN){
      Context_t* openGL_ctx = (Context_t *)glfwGetWindowUserPointer(window);
      if(key == GLFW_KEY_RIGHT){
        openGL_ctx -> eye[0] -= 1.0f;
      }else if(key == GLFW_KEY_LEFT){
        openGL_ctx -> eye[0] += 1.0f;
      }else if(key == GLFW_KEY_UP){
        openGL_ctx -> eye[1] -= 1.0f;
      }else if(key == GLFW_KEY_DOWN){
        openGL_ctx -> eye[1] += 1.0f;
      }
      /*
      openGL_ctx -> center[0] = 0.0f;
      openGL_ctx -> center[1] = 0.0f;
      openGL_ctx -> center[2] = 0.0f;

      openGL_ctx -> up[0] = 0.0f;
      openGL_ctx -> up[1] = 0.0f;
      openGL_ctx -> up[2] = 1.0f;
      */
      glm_lookat(openGL_ctx -> eye, openGL_ctx -> center, openGL_ctx -> up, openGL_ctx -> view);
      glUniformMatrix4fv(openGL_ctx -> uniView, 1, GL_FALSE, (float *)openGL_ctx -> view);
    }
  }
}

void setBindingCallback(GLFWwindow *window){
 glfwSetCursorPosCallback(window, cursor_position_callback);
 glfwSetMouseButtonCallback(window, mouse_callback);
 glfwSetKeyCallback(window, key_callback);
}
