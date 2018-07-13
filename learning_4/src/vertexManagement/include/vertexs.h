GLfloat triangle[] = {
    0.0f,  0.5f,  // Vertex 1 (X, Y)
    0.5f,  -0.5f, // Vertex 2 (X, Y)
    -0.5f, -0.5f  // Vertex 3 (X, Y)
};

GLfloat triangleColored[] = {
    0.0f,  0.5f,  1.0f, 0.0f, 0.0f, // Vertex 1 (X, Y, Red, Green, Blue): Red
    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 1 (X, Y, Red, Green, Blue): Green
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 1 (X, Y, Red, Green, Blue): Blue
};


GLfloat cube[] = {
  1.000000f, -1.000000f, -1.000000f,
  1.000000f, -1.000000f, 1.000000f,
  -1.000000f, -1.000000f, 1.000000f,
  -1.000000f, -1.000000f, -1.000000f,
  1.000000f, 1.000000f, -1.000000f,
  1.000000f, 1.000000f, 1.000001f,
  -1.000000f, 1.000000f, 1.000000f,
  -1.000000f, 1.000000f, -1.000000f
};
float vertices[] = {
    -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
    -0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
};

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
