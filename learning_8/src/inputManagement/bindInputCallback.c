#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "../../includes/glad/glad.h"
#include <GLFW/glfw3.h>
#include <cglm/call.h>


#include "../objectManagement/includes/constructor.h"
#include "../window/includes/windowManager.h"
#include "../shadersManagement/includes/shadersManager.h"


/*unused*/
Context_t* contextInstance() {
    static Context_t* openGL_ctx_instance;
    return openGL_ctx_instance;
}



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
  bool isLeft = false;
  bool isRight = false;
  bool isUp = false;
  bool isdown = false;

  if (coordinate.X > xpos) {
   isLeft = true;
   printf("isLeft !\n");
  }else if (coordinate.X < xpos) {
   isRight = true;
   printf("isRight !\n");
  }
  if (coordinate.Y < ypos) {
   isUp = true;
   printf("isUp !\n");
  }else if (coordinate.Y > ypos) {
   isdown = true;
   printf("isdown !\n");
  }




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

GLfloat getRadiansFromDegrees(GLfloat degrees){
   const GLfloat pi = 3.14159265359f;
   /*near equivalent to (pi / 180)*/
   const GLfloat radiansConvert = 0.017453292519943295;
   return degrees * radiansConvert;
   /*return degrees * pi / 180;*/
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

      float pi = 3.14159265359f;
      float radius = 10.0f;

      static GLfloat yaw = 0;
      static GLfloat pitch = 0;
      static GLfloat roll = 0;

      struct Coodinate_2D coordinate2D;
      struct Coodinate_3D coordinate3D;

      GLfloat incrementFactor = 5.0f;

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

      openGL_ctx -> center[0]  = 0.0f;
      openGL_ctx -> center[1]  = 0.0f;
      openGL_ctx -> center[2]  = 0.0f;

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
};
