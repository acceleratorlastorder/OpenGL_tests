// Window dimensions
typedef struct {
  int width;
  int height;
} screenRes;

void setWindowProperties(screenRes *monitorRes);
struct Coodinate_2D getWindowMiddlePos(screenRes *monitorRes);
