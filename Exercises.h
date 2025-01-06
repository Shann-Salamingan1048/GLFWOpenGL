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
public:
	~Exercises() = default;
private:
	const GLuint WIDTH = 800, HEIGHT = 600;
	GLFWwindow* window;
	void initGLFW();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow* window);
public:
	void helloTriangle2_3(); // Add more Triangles
	void helloTriangle2_4(); // Add more Triangles using two different VAOs and VBOs
	void helloTriangle2_5(); // second program uses dfifferent fragment shaders, one is yellow and one is orange

	void shaderUniforms3_1(); // update uniform color in fragment shader
	void shaderInterpolation3_2(); // Interpolation
	void shaderExercise3_3(); // adjust the vertex shader so that the triangle is upside down
	void shaderExercise3_4(); // move the triangle at the right side of the screen
	void shaderExercise3_5(); // set the color of the triangle equal to the position of the vertex

};