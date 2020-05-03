#include <stdio.h>

void readFile(char *charArray, char *filePath) {
  int c;
  FILE *file;
  file = fopen(filePath, "r");
  if (file) {
    int i = 0;
    while ((c = getc(file)) != EOF) {
      charArray[i] = c;
      //For debug only if need to see a print of the file
      //putchar(c);
      i++;
    }
    fclose(file);
    charArray[i - 1] = '\0';
  }
}
