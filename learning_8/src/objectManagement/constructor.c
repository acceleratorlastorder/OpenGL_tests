#include "includes/constructor.h"


/**
 *
 *
 */
void init_mat4_with_GLM_MAT4_IDENTITY_INIT (mat4 matrice){
  matrice[0][0] = 1.0f;
  matrice[0][1] = 0.0f;
  matrice[0][2] = 0.0f;
  matrice[0][3] = 0.0f;
  matrice[1][0] = 0.0f;
  matrice[1][1] = 1.0f;
  matrice[1][2] = 0.0f;
  matrice[1][3] = 0.0f;
  matrice[2][0] = 0.0f;
  matrice[2][1] = 0.0f;
  matrice[2][2] = 1.0f;
  matrice[2][3] = 0.0f;
  matrice[3][0] = 0.0f;
  matrice[3][1] = 0.0f;
  matrice[3][2] = 0.0f;
  matrice[3][3] = 1.0f;
  return;
}
