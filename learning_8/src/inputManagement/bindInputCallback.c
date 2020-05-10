#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "../../includes/glad/glad.h"
#include <GLFW/glfw3.h>
#include <cglm/call.h>


#include "../objectManagement/includes/constructor.h"
#include "../window/includes/windowManager.h"
#include "../shadersManagement/includes/shadersManager.h"

#include "includes/keyboardMapping.h"

/*unused an need rework useless for now
#define KEYBOARD_LAYOUT_SIZE 128
typedef int* keyboardLayout_t[KEYBOARD_LAYOUT_SIZE];

keyboardLayout_t keyBoardLayout[KEYBOARD_LAYOUT_SIZE];

Context_t* contextInstance() {
    static Context_t* openGL_ctx_instance;
    return openGL_ctx_instance;
};

void setKeyboardLayout(keyboardLayout_t* newLayout){
 for (size_t i = 0; i < KEYBOARD_LAYOUT_SIZE; i++) {
  keyBoardLayout[i] = newLayout[i];
 }
};
*/

GLfloat getRadiansFromDegrees(GLfloat degrees){
   /*const GLfloat pi = 3.14159265359f;*/
   /*near equivalent to (pi / 180)*/
   const GLfloat radiansConvert = 0.017453292519943295;
   return degrees * radiansConvert;
   /*return degrees * pi / 180;*/
};

struct Coodinate_3D get3DPositionForCursor(GLfloat yaw, GLfloat pitch){
   GLfloat X = cos(getRadiansFromDegrees(yaw)) * cos(getRadiansFromDegrees(pitch));
   GLfloat Y = sin(getRadiansFromDegrees(pitch));
   GLfloat Z = sin(getRadiansFromDegrees(yaw)) * cos(getRadiansFromDegrees(pitch));

   return (Coodinate_3D){X, Y, Z};
};

struct Coodinate_3D get3DPosition(GLfloat yaw, GLfloat pitch, GLfloat radius){
   GLfloat phi = cos(getRadiansFromDegrees(pitch)) * radius;

   GLfloat X = cos(getRadiansFromDegrees(yaw)) * phi;
   GLfloat Y = sin(getRadiansFromDegrees(pitch)) * radius;
   GLfloat Z = sin(getRadiansFromDegrees(yaw)) * phi;

   return (Coodinate_3D){X, Y, Z};
};

struct Coodinate_2D get2DPointCoordinateInTheCirclePerimeter(struct Coodinate_2D *coordinate, GLfloat radius, GLfloat theta){
   return (Coodinate_2D){coordinate -> X + (radius * cos(theta)), coordinate -> Y + (radius * sin(theta))};
};

struct Coodinate_2D get90_Degres_2DPointCoordinateInTheCirclePerimeter(GLfloat radius){
   const GLfloat pi = 3.14159265359f;
   return get2DPointCoordinateInTheCirclePerimeter(&(struct Coodinate_2D){0.0f, 0.0f}, radius, pi / 2);
};

struct Coodinate_2D get180_Degres_2DPointCoordinateInTheCirclePerimeter(GLfloat radius){
   const GLfloat pi = 3.14159265359f;
   return get2DPointCoordinateInTheCirclePerimeter(&(struct Coodinate_2D){0.0f, 0.0f}, radius, pi);
};

struct Coodinate_2D get270_Degres_2DPointCoordinateInTheCirclePerimeter(GLfloat radius){
   const GLfloat pi = 3.14159265359f;
   return get2DPointCoordinateInTheCirclePerimeter(&(struct Coodinate_2D){0.0f, 0.0f}, radius, 3 * pi / 2);
};

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
 /* sample to get the cursor pos outside of the callback
 double xpos, ypos;
 glfwGetCursorPos(window, &xpos, &ypos);
 */
 printf("cursor moved callback xpos: %f, ypos: %f\n", xpos, ypos);

 Context_t* openGL_ctx = (Context_t *)glfwGetWindowUserPointer(window);

 struct Coodinate_2D coordinate = getWindowMiddlePos(&openGL_ctx -> ScreenRes);

 printf("cursor moved callback xpos: %f, ypos: %f\n", coordinate.X, coordinate.Y);

  /*
   add test to see if we're looking left, right, up, down, then evolve this into moving the camera in the direction the mouse is
   might try simple first then add a percentage of rotation depending on the max/min value are and then rotate
   ex: width 800 middle is at 400, so between 0 and 400 is left, 200 is 50% of rotation in the left direction then we're doing a 90° rotation
   after testing that implementing an fps like camera with sensibility parameter will be the objective
   ex: mouse at 200px 50% left then, sensitivity 50%, so 25% of the initial rotation will be done
  */

  static double lastXpos = 0;
  static double lastYpos = 0;
  static bool firstMove = false;

  if(firstMove) {
    firstMove = false;
    lastXpos = xpos;
    lastYpos = ypos;
  }

  static GLfloat yaw = 0;
  static GLfloat pitch = 0;
  /*static GLfloat roll = 0;*/
  float sensitivity = 0.05;

  double xoffset = xpos - lastXpos;
  double yoffset = lastYpos - ypos;

  lastXpos  = xpos;
  lastYpos  = ypos;

  xoffset  *= sensitivity;
  yoffset  *= sensitivity;

  yaw      += xoffset;
  pitch    += yoffset;

  if(pitch > 89.0f){
   pitch = 89.0f;
  }
  if(pitch < -89.0f){
   pitch = -89.0f;
  }


  struct Coodinate_3D coordinate3D;
  coordinate3D = get3DPositionForCursor(yaw, pitch);

  vec3 coordinateNormalised;
  coordinateNormalised[0] = coordinate3D.X;
  coordinateNormalised[1] = coordinate3D.Y;
  coordinateNormalised[2] = coordinate3D.Z;


  //glm_vec3_normalize(coordinateNormalised);

  openGL_ctx -> center[0]  = coordinateNormalised[0];
  openGL_ctx -> center[1]  = coordinateNormalised[1];
  openGL_ctx -> center[2]  = coordinateNormalised[2];


  glm_lookat(openGL_ctx -> eye, openGL_ctx -> center, openGL_ctx -> up, openGL_ctx -> view);
  glUniformMatrix4fv(openGL_ctx -> uniView, 1, GL_FALSE, (float *)openGL_ctx -> view);
}



static void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
 printf("yooo button: %d, action: %d, mods: %d\n", button, action, mods);
 if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
  /*Context_t* openGL_ctx = (Context_t *)glfwGetWindowUserPointer(window);*/
  printf("left !!!\n");
  /*getCenter(openGL_ctx -> center, window);*/


 }
};

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
    static float radius = 10.0f;


    if(key == GLFW_KEY_RIGHT || key == GLFW_KEY_LEFT || key == GLFW_KEY_UP || key == GLFW_KEY_DOWN || key == GLFW_KEY_S || key == GLFW_KEY_W){
      Context_t* openGL_ctx = (Context_t *)glfwGetWindowUserPointer(window);

      static GLfloat yaw = 0;
      static GLfloat pitch = 0;
      /*static GLfloat roll = 0;*/

      struct Coodinate_3D coordinate3D;

      GLfloat incrementFactor = 5.0f;


      if (key == GLFW_KEY_W) {
       radius--;
      }else if (key == GLFW_KEY_S) {
       radius++;
      }

      if(key == GLFW_KEY_RIGHT){
        yaw += incrementFactor;
      }else if(key == GLFW_KEY_LEFT){
        yaw -= incrementFactor;
      }
      if(key == GLFW_KEY_UP){
        pitch += incrementFactor;
      }else if(key == GLFW_KEY_DOWN){
        pitch -= incrementFactor;
      }



      coordinate3D = get3DPosition(yaw, pitch, radius);



      /*printf("glfwGetTime() %ld, sin(glfwGetTime()): %ld, cos(glfwGetTime()): %ld \n", glfwGetTime(), sin(glfwGetTime()), cos(glfwGetTime()));*/

      /*
      if(key == GLFW_KEY_RIGHT){
        openGL_ctx -> eye[0] -= 1.0f;
      }else if(key == GLFW_KEY_LEFT){
        openGL_ctx -> eye[0] += 1.0f;
      }else if(key == GLFW_KEY_UP){
        openGL_ctx -> eye[1] -= 1.0f;
      }else if(key == GLFW_KEY_DOWN){
        openGL_ctx -> eye[1] += 1.0f;
      }*/

      openGL_ctx -> eye   [0]  = coordinate3D.X;
      openGL_ctx -> eye   [1]  = coordinate3D.Y;
      openGL_ctx -> eye   [2]  = coordinate3D.Z;
      /*
      openGL_ctx -> center[0]  = 0.0f;
      openGL_ctx -> center[1]  = 0.0f;
      openGL_ctx -> center[2]  = 0.0f;
      */
      /**
       * up will kind of be the roll of the camera this doesn't really change for a normal fps view
       * keep it at 0, 1, 0 for now, will be usefull to change it's value in VR mode or in some sort of plane simulator maybe,
       * but for now we're far from this
       **/
      openGL_ctx -> up    [0]  = 0.0f;
      openGL_ctx -> up    [1]  = 1.0f;
      openGL_ctx -> up    [2]  = 0.0f;

      glm_lookat(openGL_ctx -> eye, openGL_ctx -> center, openGL_ctx -> up, openGL_ctx -> view);
      glUniformMatrix4fv(openGL_ctx -> uniView, 1, GL_FALSE, (float *)openGL_ctx -> view);
    }
  }
};

void setBindingCallback(GLFWwindow *window){
 glfwSetCursorPosCallback(window, cursor_position_callback);
 glfwSetMouseButtonCallback(window, mouse_callback);
 glfwSetKeyCallback(window, key_callback);
 glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
};
