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
#include <stb/stb_images.h>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Transformations
{
public:
	~Transformations() = default;
private:
	const GLuint WIDTH = 800, HEIGHT = 600;
	GLFWwindow* window;
	void initGLFW();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow* window, float &x , float &y);
	void processInput(GLFWwindow* window);

public:
	void Exercise5_1(); // rotate the object and move it hehehe
	// translate and then rotate
	void Exercise5_2ex1(); // rotate and then translate
	void Exercise5_2ex2(); // rotate and then translate and then second container
};