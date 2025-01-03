#pragma once
#include <iostream>
// GLAD
#include <glad/glad.h>
// GLFW
#include <GLFW/glfw3.h>
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Exercises
{
private:
	const GLint WIDTH = 800, HEIGHT = 600;
	GLFWwindow* window;
	void initGLFW();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow* window);
public:
	void helloTriangle2_3(); // Add more Triangles
	void helloTriangle2_4(); // Add more Triangles using two different VAOs and VBOs
	void helloTriangle2_5(); // second program uses dfifferent fragment shaders, one is yellow and one is orange
};