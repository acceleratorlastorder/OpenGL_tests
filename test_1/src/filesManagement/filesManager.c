#include <stdio.h>
#include <time.h>

void readFile(char *charArray, char *filePath) {
  int c;
  FILE *file;
  file = fopen(filePath, "r");
  if (file) {
    int i = 0;
    while ((c = getc(file)) != EOF) {
      charArray[i] = c;
      // putchar(c);
      i++;
    }
    fclose(file);
    charArray[i - 1] = '\0';
  }
}
