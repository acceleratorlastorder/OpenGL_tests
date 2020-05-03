#define monitorWidth 800
#define monitorHeight 600

#include "../objectManagement/includes/constructor.h"


void setWindowProperties(ScreenRes *monitorRes){
 monitorRes -> width = monitorWidth;
 monitorRes -> height = monitorHeight;
};

struct Coodinate_2D getWindowMiddlePos(ScreenRes *monitorRes){
 return (Coodinate_2D){monitorRes -> width / 2, monitorRes -> height / 2};
};
