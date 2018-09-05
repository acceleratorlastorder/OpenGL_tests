#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "../../../includes/glad/glad.h"

#include <GLFW/glfw3.h>

#include "../../../includes/include.h"

#include "../../objectManagement/includes/constructor.h"

#include "includes/getBmp_textures.h"

GLuint loadBMP_custom(const char *imagepath, Context_t *ctx) {

  // Data read from the header of the BMP file
  unsigned char header[54]; // Each BMP file begins by a 54-bytes header
  unsigned int dataPos;     // Position in the file where the actual data begins
  unsigned int width, height;
  unsigned int imageSize; // = width*height*3
  // Actual RGB data
  unsigned char *data;

  // Open the file
  FILE *file = fopen(imagepath, "rb");
  if (!file) {
    puts("Image could not be opened");
    return 0;
  }
  // If not 54 bytes read : problem
  if (fread(header, 1, 54, file) != 54) {
    puts("Not a correct BMP file");
    return 1;
  }
  if (header[0] != 'B' || header[1] != 'M') {
    puts("Not a correct BMP file");
    return 0;
  }
  // Read ints from the byte array
  dataPos = *(int *)&(header[0x0A]);
  imageSize = *(int *)&(header[0x22]);
  width = *(int *)&(header[0x12]);
  height = *(int *)&(header[0x16]);

  // Some BMP files are misformatted, guess missing information
  if (imageSize == 0) {
    // 3 : one byte for each Red, Green and Blue component
    imageSize = width * height * 3;
  }
  if (dataPos == 0) {
    dataPos = 54; // The BMP header is done that way
  }

  // Create a buffer
  data = malloc(imageSize);

  // Read the actual data from the file into the buffer
  fread(data, 1, imageSize, file);

  // Everything is in memory now, the file can be closed
  fclose(file);

  // Create one OpenGL texture
  glGenTextures(1, &ctx->tex);

  // "Bind" the newly created texture : all future texture functions will modify
  // this texture
  glBindTexture(GL_TEXTURE_2D, ctx->tex);

  // Give the image to OpenGL
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT,
               GL_UNSIGNED_BYTE, data);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glGenerateMipmap(GL_TEXTURE_2D);

  return ctx->tex;
}


/*
unsigned char getImageInMemory(unsigned char *data, unsigned int imageSize,
                               FILE *file) {}
*/
