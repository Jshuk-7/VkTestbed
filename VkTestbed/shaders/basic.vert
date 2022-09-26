#version 450

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec3 a_Color;

layout (location = 0) out vec4 f_Color;

void main()
{
	gl_Position = vec4(a_Position, 0.0, 1.0);
	f_Color = vec4(a_Color, 1.0);
}