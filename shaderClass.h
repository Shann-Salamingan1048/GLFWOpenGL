#pragma once
#include <glad/glad.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>

std::string getFileContent(const std::string& fileName);
class Shader
{
public:
	GLuint ID;
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	Shader() = default;
	void fragShadeOnly(const std::string& fragmentPath);
	void vertShadeOnly(const std::string& vertexPath);

	void Activate();
	void Delete();

private:
	void CheckCompileErrors(GLuint shader, const std::string& type);


};