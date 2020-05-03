#define monitorWidth 800
#define monitorHeight 600

#include "includes/windowManager.h"
#include "../objectManagement/includes/constructor.h"


void setWindowProperties(screenRes *monitorRes){
 monitorRes -> width = monitorWidth;
 monitorRes -> height = monitorHeight;
};

struct Coodinate_2D getWindowMiddlePos(screenRes *monitorRes){
 return (Coodinate_2D){monitorRes -> width / 2,monitorRes -> height / 2};
}
