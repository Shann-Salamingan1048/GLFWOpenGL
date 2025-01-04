#pragma once
#include <glad/glad.h>
// Element Buffer Object (EBO)
class EBO
{
public:
	GLuint ID = 0;
	EBO(GLuint* indices, GLsizeiptr size);
	void Bind();
	void Unbind();
	void Delete();
};