#version 450 compatibility

// Input vertex data, different for all executions of this shader.
/*
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
*/
in vec2 position;
in vec2 texcoord;

// Output data ; will be interpolated for each fragment.
out vec2 Texcoord;

in vec3 color;
out vec3 Color;

void main(){
    Color = color;
    Texcoord = texcoord;
    gl_Position = vec4(position, 0.0, 1.0);
}
