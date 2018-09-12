#version 450 compatibility
/*
in vec3 Color;
in vec2 texcoord;

out vec4 outColor;
out vec2 Texcoord;

uniform sampler2D tex;

void main()
{
    outColor = texture(tex, Texcoord) * vec4(Color, 1.0);
}
*/


// Interpolated values from the vertex shaders
in vec3 Color;
in vec2 Texcoord;

// Ouput data
out vec4 outColor;

// Values that stay constant for the whole mesh.
uniform sampler2D tex;

void main(){
    outColor = texture(tex, Texcoord) * vec4(Color, 1.0);
}
