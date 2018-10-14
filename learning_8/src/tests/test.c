#include "../objectManagement/includes/constructor.h"
#include "./includes/test.h"

void initTest(){
 TEST_ArrayOf_VertexAttribParameter_t_push();
};




void TEST_ArrayOf_VertexAttribParameter_t_push(){
 ArrayOf_VertexAttribParameter_t ArrayOf_VertexAttribParameter_s;
 VertexAttribParameter_t verAttrib_s;

 TEST_Init_VertexAttribParameter_t(&verAttrib_s);

 ArrayOf_VertexAttribParameter_t_initArray(&ArrayOf_VertexAttribParameter_s, 0);
 ArrayOf_VertexAttribParameter_t_push(&ArrayOf_VertexAttribParameter_s, &verAttrib_s);
};



void TEST_Init_VertexAttribParameter_t(VertexAttribParameter_t *verAttrib_s){
 printf("createTestStruct() start\n");
 
 verAttrib_s->attributeLocation = 1;
 verAttrib_s->size = 2;
 verAttrib_s->type = GL_FLOAT;
 verAttrib_s->normalized = GL_FALSE;
 verAttrib_s->stride = (8 * sizeof(GLfloat));
 verAttrib_s->pointer = (void *)(6 * sizeof(GLfloat));
 verAttrib_s->name = malloc(strlen("texcoord") + 1);
 strcpy(verAttrib_s->name, "texcoord");

 printf("createTestStruct() end\n");
 return;
}
