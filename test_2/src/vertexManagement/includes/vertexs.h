//check how to make dynamc array
/*GLfloat *verticesArray[] = {
  {
      0.0f,  0.5f,
      0.5f,  -0.5f,
      -0.5f, -0.5f
  },{
      0.0f,  0.5f,  1.0f, 0.0f, 0.0f,
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,
      -0.5f, -0.5f, 0.0f, 0.0f, 1.0f
  },{
    1.000000f, -1.000000f, -1.000000f,
    1.000000f, -1.000000f, 1.000000f,
    -1.000000f, -1.000000f, 1.000000f,
    -1.000000f, -1.000000f, -1.000000f,
    1.000000f, 1.000000f, -1.000000f,
    1.000000f, 1.000000f, 1.000001f,
    -1.000000f, 1.000000f, 1.000000f,
    -1.000000f, 1.000000f, -1.000000f
  }
};*/
/*
struct vertex {

};*/


void getVertexs (Context_t *ctx);
void uploadVertexOntoTheGPU(Context_t *ctx);
