#pragma once
// Vertex Buffer Object (VBO)
#include <glad/glad.h>


class VBO
{
public:
	GLuint ID = 0;
	VBO(GLfloat* vertices, GLsizeiptr size);
	void Bind();
	void Unbind();
	void Delete();


};
