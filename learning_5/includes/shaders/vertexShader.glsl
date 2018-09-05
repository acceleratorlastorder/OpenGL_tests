#version 450 compatibility

in vec2 position;
in vec2 texcoord;
in vec3 color;

out vec3 Color;
out vec2 Texcoord;

void main()
{
    Color = color;
    gl_Position = vec4(position, 0.0, 0.7);
    Texcoord = texcoord;
}
