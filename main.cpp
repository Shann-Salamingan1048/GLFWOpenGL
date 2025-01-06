#include <iostream>
// GLAD
#include <glad/glad.h>
// GLFW
#include <GLFW/glfw3.h>
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Exercises.h"
#include "Exercises2.h"
int main()
{
	Exercises ex;
	//ex.helloTriangle2_3();
	//ex.helloTriangle2_4();
	//ex.helloTriangle2_5();
	//ex.shaderUniforms3_1();
	//ex.shaderInterpolation3_2();
	//ex.shaderExercise3_3();
	//ex.shaderExercise3_4();
	//ex.shaderExercise3_5();

	Exercises2 ex2;
	//ex2.TextureExercise4_1();
	//ex2.TextureExercise4_2();
	//ex2.TextureExercise4_4();
	//ex2.TextureExercise4_5();
	ex2.TextureExercise4_6();
	
	return EXIT_SUCCESS;
}