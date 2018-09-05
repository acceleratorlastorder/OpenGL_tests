#ifdef debugBuild
#include <stdio.h>
#endif

#include "../../includes/glad/glad.h"

#include <GLFW/glfw3.h>

#include "../../includes/include.h"

#include "../objectManagement/includes/constructor.h"

#include "../filesManagement/pictureManagement/includes/getBmp_textures.h"

#include "includes/texturesManagement.h"

void getTexture(Context_t *ctx) {
/*
  glGenTextures(1, &ctx->tex);
  glBindTexture(GL_TEXTURE_2D, ctx->tex);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  float color[] = {1.0f, 0.0f, 0.0f, 1.0f};
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glGenerateMipmap(GL_TEXTURE_2D);

  loadTextureImage(ctx);

  */

  loadBMP_custom("assets/images/textures/Carbon_03.bmp", ctx);


}

void loadTextureImage(Context_t *ctx) {
  // Black/white checkerboard
  float pixels[] = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
                    1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
}
