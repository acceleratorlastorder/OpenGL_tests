#define isFullscreen 0
#define framePerSec 60
#define usedVertex 1


// Window dimensions
typedef struct {
  int width;
  int height;
} screenRes;

char usableVertex[3][50];


double getMsBetweenFrame();
void readFile(char *charArray, char *filePath);
void fillStringWithNull(char *stringToReset);
void removeStringFromMemory(char *stringToReset);
void error_callback(int error, const char *description);
void setBootstrapConfig(void);
void clearScreen(void);
