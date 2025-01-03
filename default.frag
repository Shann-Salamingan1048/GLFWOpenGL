#version 330 core
out vec4 FragColor;

uniform vec4 ourColorDawKuno;
in vec4 vertexColor;
void main()
{
	FragColor = ourColorDawKuno;
};