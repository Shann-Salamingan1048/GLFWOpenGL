#pragma once
#include <glad/glad.h>
// Element Buffer Object (EBO)
class EBO
{
public:
	GLuint ID;
	EBO(GLuint* indices, GLsizeiptr size);
	void Bind();
	void Unbind();
	void Delete();
};