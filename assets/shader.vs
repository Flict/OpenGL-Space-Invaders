#version 330

in vec4 color;
in vec4 position;
in vec2 texCoord;

uniform vec2 offset;
uniform mat4 transform;

out vec4 Color;
out vec2 TexCoord;

void main()
{
	TexCoord = texCoord;
	Color = color;
	gl_Position = transform * position;
	gl_Position.xy += offset;
}