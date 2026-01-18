#version 330 core
uniform int isBorder;
in vec4 out_Color;
out vec4 FragColor;

void main()
{
	FragColor = vec4(out_Color);
}