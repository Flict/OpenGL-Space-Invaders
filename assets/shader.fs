#version 330

in vec4 Color;
in vec2 TexCoord;

out vec4 outputColor;

uniform sampler2D tex;

void main()
{
	outputColor = texture(tex, TexCoord) * Color;
}