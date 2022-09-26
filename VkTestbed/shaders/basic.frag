#version 450

layout (location = 0) out vec4 vk_Color;

layout (location = 0) in vec4 f_Color;

void main()
{
	vk_Color = f_Color;
}