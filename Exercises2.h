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
	const GLuint WIDTH = 800, HEIGHT = 600;
	GLFWwindow* window;
	void initGLFW();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow* window);

public:
	void TextureExercise4_1();
	void TextureExercise4_2(); // combined Texture
	// the TextureExercise4_2() has TextureExercise4_3 in it, please see the exercise4_2.vert and exercise4_2.frag
	// the TextureExercise4_3 the haappy face is in the reverse direction, please see the exercise4_3.vert and exercise4_3.frag
	void TextureExercise4_4(); // manipulate the text choord
	void TextureExercise4_5(); // change the gl_linear to gl_nearest 
	// gl_linear is the default value for the magnification and minification filter or do interpolation
	// gl_nearest is the nearest pixel value or no interpolation and you can see the pixel clearly
	// interpolation is the process of determining the color of the pixel based on the color of the surrounding pixels

	void TextureExercise4_6(); // manipulate the mix function third parameter
};