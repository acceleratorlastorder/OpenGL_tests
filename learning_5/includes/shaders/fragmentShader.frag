#version 450 compatibility

in vec3 Color;
in vec2 texcoord;

out vec4 outColor;
out vec2 Texcoord;

uniform sampler2D tex;

void main()
{
    outColor = texture(tex, Texcoord) * vec4(Color, 1.0);
}
