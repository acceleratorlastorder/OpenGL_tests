#version 450 compatibility

// Input vertex data, different for all executions of this shader.
/*
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
*/
in vec3 position;
in vec3 color;
in vec2 texcoord;

// Output data; will be interpolated for each fragment.
out vec2 Texcoord;
out vec3 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform vec3 overrideColor;

void main(){
    Color = /*overrideColor */color;
    Texcoord = texcoord;
    gl_Position = proj * view * model * vec4(position, 1.0);
}
