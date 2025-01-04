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

class Exercises2
{
public:
	~Exercises2() = default;
private:
	const GLint WIDTH = 800, HEIGHT = 600;
	GLFWwindow* window;
	void initGLFW();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow* window);

public:
	void TextureExercise4_1();

};