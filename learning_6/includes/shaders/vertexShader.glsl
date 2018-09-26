#version 450 compatibility

// Input vertex data, different for all executions of this shader.
/*
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
*/
in vec3 position;
in vec2 texcoord;

// Output data; will be interpolated for each fragment.
out vec2 Texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

in vec3 color;
out vec3 Color;

void main(){
    Color = color;
    Texcoord = texcoord;
    gl_Position = proj * view * model * vec4(position, 1.0);
}
